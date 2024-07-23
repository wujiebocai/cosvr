#pragma once

#include <chrono>
#include <ctime>
#include <locale>
#include <iomanip>
#include <sstream>
#include <tuple>

namespace modules::timer {
	static inline int64_t get_time_seconds() {
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	static inline int64_t get_time_milliseconds() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	}

	static inline std::tm ltime_to_tm(const std::time_t tval) {
		return *(std::localtime(&tval));
	}

	static inline std::time_t tm_to_ltime(const std::tm& t) {
		return std::mktime(const_cast<std::tm*>(&t));
	}

	static inline std::tm get_cur_tm() {
		return ltime_to_tm(get_time_seconds());
	}

	static inline bool str_to_tm(std::tm& t, const char* timestring, const char* format = "%Y-%m-%d %H:%M:%S") {
		if (timestring == nullptr) {
			return false;
		}
		t = {};
		std::istringstream ss(timestring);
		ss.imbue(std::locale("de_DE.utf-8"));
		ss >> std::get_time(&t, format);
		if (ss.fail()) {
			return false;
		}
		return true;
	}

	static inline std::string tm_to_str(const std::tm& t, const char* format = "%Y-%m-%d %H:%M:%S") {
		std::string str;
		str.resize(128);
		std::strftime(str.data(), str.size(), format, &t);
		return str;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 参数顺序(Y-M-D H:M:S)
	template<class ...Args>
	static inline std::time_t cal_time(Args&&... args) {
		constexpr std::size_t argslen = sizeof ...(args);
		std::tm t = get_cur_tm();
		std::tuple<Args...> tp(std::forward_as_tuple(std::forward<Args>(args)...));
		if constexpr (argslen == 6) {
			std::tie(t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec) = tp;
			t.tm_year -= 1900;
			t.tm_mon -= 1;
		}
		else if constexpr (argslen == 5) {
			std::tie(t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec) = tp;
			t.tm_mon -= 1;
		}
		else if constexpr (argslen == 4) {
			std::tie(t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec) = tp;
		}
		else if constexpr (argslen == 3) {
			std::tie(t.tm_hour, t.tm_min, t.tm_sec) = tp;
		}
		else if constexpr (argslen == 2) {
			std::tie(t.tm_min, t.tm_sec) = tp;
		}
		else if constexpr (argslen == 1) {
			std::tie(t.tm_sec) = tp;
		}
		return std::mktime(&t);
	}
	
	struct t_loop_time {
		std::tm t_ = {};
		const int type_ = -1; //-1:未定义, 5:月轮询, 4:日轮询, 3:小时轮询, 2:分钟轮询, 1:秒钟轮询
	};
	// 参数顺序(Y-M-D H:M:S)
	template<class... Args>
	static inline t_loop_time cal_loop_time(Args&&... args) {
		constexpr std::size_t argslen = sizeof ...(args);
		std::tm t = get_cur_tm();
		auto tp(std::forward_as_tuple(std::forward<Args>(args)...));
		if constexpr (argslen == 5) {
			std::tie(t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec) = tp;
			t.tm_mon -= 1;
		}
		else if constexpr (argslen == 4) {
			std::tie(t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec) = tp;
		}
		else if constexpr (argslen == 3) {
			std::tie(t.tm_hour, t.tm_min, t.tm_sec) = tp;
		}
		else if constexpr (argslen == 2) {
			std::tie(t.tm_min, t.tm_sec) = tp;
		}
		else if constexpr (argslen == 1) {
			std::tie(t.tm_sec) = tp;
		}
		return t_loop_time{ t, argslen };
	}
	static inline std::time_t cal_loop_next_time(t_loop_time& lt) {
		if (lt.type_ <= 0) {
			return -1;
		}
		std::tm t = get_cur_tm();
		auto curtime = std::mktime(&t);
		auto settime = std::mktime(&lt.t_);
		auto& sett = lt.t_;
		switch (lt.type_) {
		case 5: {
			while (settime <= curtime) {
				sett.tm_year = t.tm_year + 1;
				settime = std::mktime(&sett);
			}
			return (settime - curtime);
		}
		case 4: {
			while (settime <= curtime) {
				sett.tm_mon = (t.tm_mon + 1) % 12;
				settime = std::mktime(&sett);
			}
			return (settime - curtime);
		}
		case 3: {
			while (settime <= curtime) {
				settime += 86400;
			}
			sett = ltime_to_tm(settime);
			return (settime - curtime);
		}
		case 2: {
			while (settime <= curtime) {
				settime += 3600;
			}
			sett = ltime_to_tm(settime);
			return (settime - curtime);
		}
		case 1: {
			while (settime <= curtime) {
				settime += 60;
			}
			sett = ltime_to_tm(settime);
			return (settime - curtime);
		}
		default:
			break;
		}
		return 0;
	}

	static inline bool set_day(std::tm& t, int day) {
    	//if (day < 1 || day > 31) {
        //	throw std::out_of_range("Invalid day");
    	//}

    	if (t.tm_mon != 1) { 
        	if ((t.tm_mon < 7 && t.tm_mon % 2 == 0) || (t.tm_mon >= 7 && t.tm_mon % 2 == 1)) {
            	if (day > 31) {
					day = 31;
            	}
        	} else {
            	if (day > 30) {
					day = 30;
            	}
        	}
    	} else {
        	bool isLeapYear = (t.tm_year % 4 == 0 && t.tm_year % 100 != 0) || (t.tm_year % 400 == 0);
        	if (isLeapYear && day > 29) {
				day = 29;
        	} else if (!isLeapYear && day > 28) {
				day = 28;
        	}
    	}

    	t.tm_mday = day;

		return true;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	static inline bool is_leep_year(const int year) {
		if ((year % 100 == 0 && year % 400 == 0) || year % 4 == 0) {
			return true;
		}
		return false;
	}

	static inline int get_week(const std::time_t tick) {
		auto tm = ltime_to_tm(tick);
		auto weekv = tm.tm_wday;
		if (weekv == 0) {
			return 7;
		}
		return weekv;
	}

	// 获取时间戳的零点时刻
	static inline std::time_t get_zero_tick(const std::time_t tick) {
		auto tm = ltime_to_tm(tick);
		tm.tm_hour = 0;
		tm.tm_min = 0;
		tm.tm_sec = 0;
		return std::mktime(&tm);
	}

	// 获取时间戳周一0点时刻
	static inline std::time_t get_monday_zero(const std::time_t tick) {
		auto tm = ltime_to_tm(tick);
		auto tmval = std::mktime(&tm);
		std::time_t weekdiff = (tm.tm_wday == 0 ? 6 : (tm.tm_wday - 1)) * 86400;
		return (tmval - weekdiff);
	}

	// 判断两个时间是否在一周内
	static inline bool is_same_week(const std::time_t tick1, const std::time_t tick2) {
		auto time1 = get_monday_zero(tick1);
		auto time2 = get_monday_zero(tick2);
		if (time1 == time2) {
			return true;
		}
		return false;
	}

	// 判断是否同一天
	static inline bool is_same_day(const std::time_t tick1, const std::time_t tick2) {
		auto tm1 = ltime_to_tm(tick1);
		auto tm2 = ltime_to_tm(tick2);
		if (tm1.tm_year == tm2.tm_year && tm1.tm_mon == tm2.tm_mon && tm1.tm_wday == tm2.tm_wday) {
			return true;
		}
		return false;
	}
}