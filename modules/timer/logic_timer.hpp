#pragma once

#include <bnet/bnet.hpp>
#include <async_simple/coro/Lazy.h>
#include "app/iopool.hpp"
#include "time_util.hpp"
#include "time_wheel.hpp"

namespace modules {
namespace timer {
    enum timer_type {
		TIMER_LOOP = 1,
		TIMER_AFTER = 2,
		TIMER_ALOCK = 3,
		TIMER_LOOP_ALOCK = 4,
	};

	typedef std::function<void()> event_op;
	class timer_event_mgr {
	public:
        // tid
		static inline int64_t gen_tid(uint32_t val, int type) {
			return val * 10 + type;
		}
		// tid
		static inline int64_t gen_tid(t_loop_time& lt, int type) {
			auto settime = std::mktime(&lt.t_);
			return settime * 10 + type;
		}
        // get time type
		static inline int get_type(int64_t tid) {
			return tid % 10;
		}

		inline bool check(const int64_t tid) {
			auto item = tevts_.find(tid);
			if (item == tevts_.end()) {
				return false;
			}
			return true;
		}

		inline int64_t add(const int64_t tid, event_op&& fun) {
			tevts_[tid] = fun;
			return tid;
		}

		inline int remove(const int64_t tid) {
			return tevts_.erase(tid);
		}
		
		inline std::size_t bucket_count() {
			return tevts_.size();
		}

		inline bool handle(int64_t tid) {
			auto itr = tevts_.find(tid);
			if (itr == tevts_.end()) {
				return false;
			}

			if (itr->second) {
				itr->second();
			}

			auto ttype = timer_event_mgr::get_type(tid);
			if (ttype == TIMER_AFTER || ttype == TIMER_ALOCK) {
				remove(tid);
				return false;
			}
			
			return true;
		}

		using tevents_type = std::unordered_map<int64_t, event_op>; // tid-events
	private:
		tevents_type tevts_;
	};

	template<class Fn>
    concept is_co_func = std::is_invocable_r<void, Fn, std::error_code&>::value || std::is_invocable_r<bool, Fn, std::error_code&>::value;

    class logic_timer {
    public:
    	logic_timer(asio::io_context& ctx, int delay = 10) : btimer_(ctx), timer_(delay) {
			btimer_.start(std::chrono::milliseconds(delay), [this](const std::error_code& ec) mutable {
		        if (ec) {
			        std::cerr << "err: " << ec.message() << std::endl;
		        }

		        this->timer_.update();
	        });
		}

    	~logic_timer() { 
    	    btimer_.stop();
    	}

        inline void set_pause(bool flag) { timer_.set_pause(flag); }
		inline uint32_t get_cur_idx() { return timer_.get_cur_idx(); }

		inline bool cancel(const int64_t ttid) {
			return (eventmgr_.remove(ttid) > 0);
		}

		inline std::size_t bucket_count() {
			return eventmgr_.bucket_count();
		}

		template<class Fn>
		inline int64_t loop(int ms, Fn&& cb) {
			auto tid = timer_event_mgr::gen_tid(get_cur_idx(), TIMER_LOOP);
			int ret = timer_.loop(ms, [this, tid]() {
				return eventmgr_.handle(tid);
			});
			if (ret < 0) {
				return -1;
			}
			auto hfunc = [cb = std::move(cb)]() mutable {
				cb();
			};
			return eventmgr_.add(tid, std::move(hfunc));
		}

		template<class Fn>
		inline int32_t after(int ms, Fn&& cb) {
			auto tid = timer_event_mgr::gen_tid(get_cur_idx(), TIMER_AFTER);
			int ret = timer_.after(ms, [this, tid]() {
				eventmgr_.handle(tid);
				return false;
			});
			if (ret < 0) {
				return -1;
			}
			auto hfunc = [cb = std::move(cb)]() mutable {
				cb();
			};
			return eventmgr_.add(tid, std::move(hfunc));
		}

		template<class Fn, class ... Args>
		inline int32_t alarm(Fn&& cb, Args&&... args) {
			constexpr std::size_t arglen = sizeof...(args);
			if constexpr (arglen <= 0 || arglen > 6) {
				return -1;
			}
			
			auto settime = cal_time(std::forward<Args>(args)...);
			if (settime < 0) {
				return -2;
			}

			auto hfunc = [cb = std::move(cb)]() mutable {
				cb();
			};

			auto tid = timer_event_mgr::gen_tid(get_cur_idx(), TIMER_ALOCK);
			auto curtime = get_time_seconds();
			auto tick = settime - curtime;
			if (tick < 0) {
				hfunc();
				return 0;
			}

			auto ret = timer_.after((int)tick * 1000, [this, tid]() {
				eventmgr_.handle(tid);
				return false;
			});

			if (ret < 0) {
				return -3;
			}
			
			return eventmgr_.add(tid, std::move(hfunc));
		}

		template<class Fn, class... Args>
		inline int32_t loop_alarm(Fn&& cb, Args&&... args) {
			constexpr std::size_t arglen = sizeof...(args);
			if constexpr (arglen <= 0 || arglen > 5) {
				return -1;
			}

			auto looptm = cal_loop_time(std::forward<Args>(args)...);
			auto tid = timer_event_mgr::gen_tid(get_cur_idx(), TIMER_LOOP_ALOCK);
			auto ret = this->loop_alarm_t(looptm, [this, tid]() {
				return eventmgr_.handle(tid);
			});
			
			if (ret < 0) {
				return -1;
			}

			auto hfunc = [cb = std::move(cb)]() mutable {
				cb();
			};
			
			return eventmgr_.add(tid, std::move(hfunc));
		}

	protected:
		inline int loop_alarm_t(t_loop_time& looptm, cb_handler&& cb) {
			using hfunc_type = std::function<void(t_loop_time&, std::time_t)>;
			auto hfptr = std::make_shared<hfunc_type>();
			auto hf = [this, hfptr, func = std::move(cb)](t_loop_time& lptm, std::time_t tick) mutable {
				if (tick <= 0) {
					auto nexttick = loop_alarm_next_tick(lptm);
					if (func()) {
						(*hfptr)(lptm, nexttick);
					}
					return;
				}
				auto ret = timer_.after((int)tick, [this, hfptr, lptm = std::move(lptm), func]() mutable {
					auto nexttick = loop_alarm_next_tick(lptm);
					if (func()) {
						(*hfptr)(lptm, nexttick);
					}
					return false;
				});
				if (ret < 0) {
					std::cout << "timer error. ret: " << ret << std::endl;
					return;
				}
			};
			*hfptr = std::move(hf);
			(*hfptr)(looptm, loop_alarm_next_tick(looptm));

			return 1;
		}

		inline std::time_t loop_alarm_next_tick(t_loop_time& lptm) {
			auto jtime = timer_.judge_time();
			auto tick = cal_loop_next_time(lptm) * 1000 + jtime;
			return tick;
		}
    private:
        bnet::Timer btimer_;
        time_wheel<> timer_;
        timer_event_mgr eventmgr_;
    };
} // namespace modules 

using logic_timer_ptr_type = std::shared_ptr<timer::logic_timer>;

inline logic_timer_ptr_type make_logic_timer(asio::io_context& ctx, int delay = 10) {
	return std::make_shared<timer::logic_timer>(ctx, delay);
}

inline async_simple::coro::Lazy<logic_timer_ptr_type> get_global_logic_timer() {
	static thread_local logic_timer_ptr_type timerptr = nullptr;
	if (!timerptr) {
		auto ex = co_await modules::get_current_executor();
		timerptr = make_logic_timer(ex.context());
	}

	co_return timerptr;
}

} // namespace timer