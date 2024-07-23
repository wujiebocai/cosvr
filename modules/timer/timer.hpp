#pragma once

#include <bnet/bnet.hpp>
#include "app/iopool.hpp"
#include "time_util.hpp"
#include "time_wheel.hpp"

namespace modules {
namespace timer {
    class timer {
    public:
    	timer(asio::io_context& ctx, int delay = 10) : btimer_(ctx), timer_(delay) {
            btimer_.start(std::chrono::milliseconds(delay), [this](const std::error_code& ec) mutable {
		        if (ec) {
			        std::cerr << "err: " << ec.message() << std::endl;
		        }

		        this->timer_.update();
	        });
        }
        
    	~timer() { 
    		btimer_.stop();
		}

        inline int loop(int ms, cb_handler&& cb) {
		    return timer_.loop(ms, std::forward<cb_handler>(cb));
		}
            
		inline int after(int ms, cb_handler&& cb) {
		    return timer_.after(ms, std::forward<cb_handler>(cb));
		}

        inline uint32_t get_cur_idx() {
            return timer_.get_cur_idx();
        }
    private:
        bnet::Timer btimer_;
        time_wheel<> timer_;
    };


} // namespace timer

using timer_ptr_type = std::shared_ptr<timer::timer>;

inline timer_ptr_type make_timer(asio::io_context& ctx, int delay = 10) {
	return std::make_shared<timer::timer>(ctx, delay);
}

inline async_simple::coro::Lazy<timer_ptr_type> get_global_timer() {
	static thread_local timer_ptr_type timerptr = nullptr;
	if (!timerptr) {
		auto ex = co_await modules::get_current_executor();
		timerptr = make_timer(ex.context());
	}

	co_return timerptr;
}

} // namespace modules