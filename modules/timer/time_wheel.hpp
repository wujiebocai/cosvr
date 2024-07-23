#pragma once

#include <functional>
#include <memory>
#include <cmath>

namespace modules::timer {
	typedef std::function<bool()> cb_handler;

	struct tooth {
		tooth(int intervaltick, bool repeat, cb_handler&& cb)
			: raw_interval_(intervaltick)
			, remain_tick_(intervaltick)
			, call_back_(std::forward<cb_handler>(cb))
			, repeat_(repeat) {
		}

		~tooth() = default;

		inline bool operator()() {
			bool ret = false;
			if (call_back_) {
				ret = call_back_();
			}
			return ret && repeat_;
		}

		inline void cancel() {
			call_back_ = nullptr;
			repeat_ = false;
		}

		const int hander_idx_ = 0;
		const int raw_interval_ = 0;
		int remain_tick_ = 0;
		cb_handler call_back_;
		bool repeat_ = false;
		using UPTR_TYPE = std::unique_ptr<tooth>;
		UPTR_TYPE next_;
	};
    using ToothUPtr = tooth::UPTR_TYPE;

	template<int NearShift = 8, int LevelShift = 6, int LevelNum = 4>
	struct time_wheel {
		static constexpr int NearScale = 1 << NearShift;
		static constexpr int LevelScale = 1 << LevelShift;
		static constexpr int NearMask = (NearScale - 1);
		static constexpr int LevelMask = (LevelScale - 1);
		
		struct near_wheel {
			inline bool turn(ToothUPtr& ptr) {
				this->pointer_ = (this->pointer_ + 1) & NearMask;
				ptr = std::move(this->slots_[this->pointer_]);
				this->slots_[this->pointer_] = nullptr;
				
				return (0 == this->pointer_);
			}

			inline bool add_tooth(int mc, ToothUPtr& ptr) {
				if (!ptr) {
					return false;
				}
				if (mc >= max_) {
					return false;
				}
				
				int place = mc & NearMask; 
			
				ptr->remain_tick_ = 0; // left time(ms)
				ptr->next_ = std::move(slots_[place]);
				slots_[place] = std::move(ptr);
				return true;
			}

			ToothUPtr slots_[NearScale] = {};
			int pointer_ = 0; 
			const int64_t scale_ = 1; 
			const int64_t max_ = NearScale;
		};

		struct level_wheel {
			level_wheel(int lv) : lv_(lv), scale_(time_wheel::level_max(lv)), max_(time_wheel::level_max(lv+1)) { }

			inline bool turn(ToothUPtr& ptr) {
				this->pointer_ = (this->pointer_ + 1) & LevelMask; 
				ptr = std::move(this->slots_[this->pointer_]);
				this->slots_[this->pointer_] = nullptr;
		
				return (0 == this->pointer_);
			}

			inline bool add_tooth(int mc, ToothUPtr& ptr) {
				if (!ptr) {
					return false;
				}

				if (mc >= max_) {
					return false;
				}

				int place = ((mc >> (NearShift + lv_ * LevelShift)) & LevelMask);
			
				ptr->remain_tick_ = mc & (scale_ - 1); // left time(ms)
				ptr->next_ = std::move(slots_[place]);
				slots_[place] = std::move(ptr);
				return true;
			}

			ToothUPtr slots_[LevelScale] = {};
			int pointer_ = 0; 
			const int lv_ = 0;
			const int64_t scale_ = 0; 
			const int64_t max_ = 0;
		};

		inline static constexpr int64_t max_val() {
	        return ((int64_t)1 << (NearShift + LevelNum*LevelShift)) - 1;
        }

        inline static constexpr int64_t near_max() {
            return (int64_t)1 << NearShift;
        }

        inline static int64_t level_max(int lv) {
	        return (int64_t)1 << (NearShift + lv*LevelShift);
        }

		time_wheel(int delay) {
			delay_ = delay;
			if (delay_ <= 0) {
				delay_ = 1;
			}
			
            near_ = std::make_shared<near_wheel>();
            
			for (int idx = 0; idx < LevelNum; ++idx) {
				levels_[idx] = std::make_shared<level_wheel>(idx);
			}
		}

		inline void update() {
			auto now = timer::get_time_milliseconds();
			if (last_update_time_ == 0) {
				last_update_time_ = now;
			}
			auto difftime = now - last_update_time_ + lefttime_;
			auto count = difftime / delay_;
			if (count <= 0) return;
			lefttime_ = difftime % delay_;
			last_update_time_ = now;

			if (pause_) return;
			for (int64_t i = 0; i < count; i++) {
				loop_count_ = count - i;
				tick();
			}
		}

		inline void set_pause(bool flag) { pause_ = flag; }
		inline int64_t judge_time() { return (loop_count_ * delay_); }
		inline uint32_t get_cur_idx() { return gen_idx; }

		inline int loop(int ms, cb_handler&& cb) {
			return this->add_timer(ms, true, std::forward<cb_handler>(cb));
		}
		inline int after(int ms, cb_handler&& cb) {
			return this->add_timer(ms, false, std::forward<cb_handler>(cb));
		}
	protected:
		inline int add_timer(int ms, bool repeat, cb_handler&& cb) {
			if (!cb) {
				return -1;
			}
			if (ms < 0) {
				return -2;
			}
			auto tid = gen_idx++; // timer id
			auto toothuptr = std::make_unique<tooth>((int)std::ceil(ms / delay_), repeat, std::forward<cb_handler>(cb));
			if (!append(toothuptr)) {
				return -3;
			}
			return tid;
		}

		// timeout, 弹出一个事件
		inline bool provide(ToothUPtr& node) {
			if (node && (*node)()) {
				// agin, 重新加入
				return this->append(node);
			}
			return false;
		}

		// 以原设定时间, 重新加入到时间轮
		inline bool append(ToothUPtr& node) {
			if (!node) {
				return false;
			}
			auto mc = node->raw_interval_;
			if (mc > 0) {
				return append(mc, node);
			}
			return false;
		}

		inline bool append(int mc, ToothUPtr& node) {
			if (!node) {
				return false;
			}

			int relative = near_->pointer_;
            if (near_->add_tooth((mc + relative), node)) {
                return true;
            }

			for (int idx = 0; idx < LevelNum; ++idx) {
				auto wheel = this->levels_[idx];
				relative = relative + (wheel->pointer_ << (NearShift + wheel->lv_*LevelShift));
				if (wheel->add_tooth((mc + relative), node)) {
					return true;
				}
			}

			std::cout << "Exceed the maximum time that the timer can set. set time: " <<  mc << ", relative " << relative << ", max val: " << this->max_val() << std::endl;
			return false;
		}

		// 到点的齿轮上的事件，重新分布到轮子上
		inline void carry(ToothUPtr& head) {
			while (head) {
				auto next = std::move(head->next_);
				auto mc = head->remain_tick_;
				if (mc <= 0) {
					if (!provide(head)) {
						//head.reset(); //释放掉
					}
				}
				else {
					append(mc, head);
				}
				head = std::move(next);
			}
		}

		inline void tick() {
            ToothUPtr ptr = nullptr;
			auto ret = near_->turn(ptr);
			this->carry(ptr);
			if (!ret) {
				return;
			}

			for (int idx = 0; idx < LevelNum; ++idx) {
				auto wheel = this->levels_[idx];
				auto ret = wheel->turn(ptr);
				this->carry(ptr);
				if (!ret) {
					break;
				}
			}
		}

	private:
        std::shared_ptr<near_wheel> near_;
		std::shared_ptr<level_wheel> levels_[LevelNum];
		int delay_ = 0;
		bool pause_ = false;
		int64_t loop_count_ = 0;

		int64_t last_update_time_ = 0;
		int64_t lefttime_ = 0;
        uint32_t gen_idx = 1;
	};
}