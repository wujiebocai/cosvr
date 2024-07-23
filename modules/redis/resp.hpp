#pragma once

/*
DESC: RESP PROTO
RESP: https://redis.io/docs/reference/protocol-spec/#simple-strings  
*/

#include <ctype.h>
#include <math.h>
#include <climits>
#include <memory>
#include "object.hpp"
#include "define.hpp"

namespace modules::rds {
#define rislalpha(c)	(isalpha(c) || (c) == '_')
#define rislalnum(c)	(isalnum(c) || (c) == '_')
#define risdigit(c)		(isdigit(c))
#define risxdigit(c)	(isxdigit(c))
#define risspace(c)		(isspace(c))
#define risprint(c)		(isprint(c))
#define rtolower(c)		(tolower(c))

#define EOS	(-1)

#define REDIS_ERR -2
#define REDIS_OK 0

class resp_parse {
public:
	resp_parse() = default;
	~resp_parse() = default;

	resp_parse(const char* data, int len) : data_(data),  len_(len) { }

	inline int decode(object& robj) {
		if (!data_ || (len_ == 0)) {
			return REDIS_ERR;
		}

		if (curchar_ == EOS){
			next();
		}
            
		return decode_t(robj);
	}

	inline static void encode(const std::vector<std::string>& cmdvec, std::string& packdata) {
		constexpr const char* space = "\r\n";
		packdata.push_back('*');
		auto counts = cmdvec.size();
		packdata.append(std::to_string(counts));
		packdata.append(space);
		for (auto& item : cmdvec) {
			packdata.push_back('$');
			packdata.append(std::to_string(item.size()));
			packdata.append(space);
			packdata.append(item);
			packdata.append(space);
		}
	}

	inline int offset() { return idx_ - 1; }
protected:
	inline int data_len() { return len_; }
	inline int next() {
		if (data_len() <= 0 || idx_ >= data_len()) curchar_ = EOS;
		else curchar_ = static_cast<int>(data_[idx_++]);
		return curchar_;
	}

	inline void save_next() {
		buff_.push_back(this->curchar_);
		next();
	}

	inline bool test_next(int c) {
		if (idx_ >= data_len() || idx_ <= 0)
			return false;

		auto tmp = static_cast<int>(data_[idx_]);
		if (tmp == c) return true;
		else return false;
	}

	inline bool check_next(int c) {
		if (this->curchar_ == c) {
			next();
			return true;
		}
		else return false;
	}

	inline bool check_next(int c1, int c2) {
		if (this->curchar_ == c1 || this->curchar_ == c2) {
			save_next();
			return true;
		}
		else return false;
	}

	inline void esccheck(int c, const char* msg) {
		if (!c) {
			if (this->curchar_ != EOS)
				save_next(); 
			//throw_error(err::parse_failure, msg);
		}
	}

	inline void adjust_idx(int offset) {
		idx_ += offset;
		next();
	}

	inline bool is_new_line() { return (this->curchar_ == '\n' || this->curchar_ == '\r'); } //(\n, \r, \n\r, \r\n)

	inline int inclinenum() {
		int old = curchar_;
		if (!this->is_new_line()) {
			return REDIS_ERR;
		}
		next();
		if (is_new_line() && curchar_ != old)
			next();
		return REDIS_OK;
	}

	inline int read_num() {
		check_next('+', '-');
		int first = curchar_;
		if (!risdigit(curchar_)) {
			return REDIS_ERR;
		}
		save_next();
		bool ctype = 0;
		const char* expo = "Ee";
		if (first == '0' && check_next('x', 'X')) 
			expo = "Pp";
		for (;;) {
			if (check_next(expo[0], expo[1]))
				check_next('-', '+');
			if (risxdigit(this->curchar_))
				save_next();
			else if (this->curchar_ == '.') {
				ctype = 1;
				save_next();
			}
			else break;
		}
		buff_.push_back('\0');
		if (ctype) {
		}
		return REDIS_OK;
	}

	inline int read_integer(std::int8_t vt, object& obj) {
		auto ret = read_num();
		if (ret == REDIS_OK) {
			if (!this->check_next('\r') || !this->check_next('\n')) {
				//std::cout << "integer format error." << std::endl;
				return REDIS_ERR;
			}
			//std::cout << rds_types[vt] << buff_ << std::endl;
			auto val = std::stoll(buff_);
            obj = val;
			obj.type_ = vt;
		}
		return ret;
	}

	inline int read_short_str(std::int8_t vt, object& obj) {
		do {
			save_next();
			if (curchar_ == EOS) {
				return REDIS_ERR;
			}
		} while (!is_new_line()/*rislalnum(this->curchar_)*/);
		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "short string format error." << std::endl;
			return REDIS_ERR;
		}
		//std::cout << rds_types[vt] << buff_ << std::endl;
		if (vt == REDIS_TYPE_ERROR) AS_UNLIKELY {
			obj.err_code_ = server_rsp_error;
			obj.vstr_ = buff_;
			obj.type_ = vt;
		}
		else {
			obj = buff_;
			obj.type_ = vt;
		}

		return REDIS_OK;
	}

	inline int read_long_str(std::int8_t vt, object& obj) {
		int success = 0;
		auto ret = read_num();
		if (ret < 0) {
			//std::cout << "read string length fail." << std::endl;
			return REDIS_ERR;
		}
		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "string format error." << std::endl;
			return REDIS_ERR;
		}
			
		auto len = std::stoll(buff_);
		buff_.clear();
		if (len < -1 || (LLONG_MAX > SIZE_MAX && len > (long long)SIZE_MAX)) {
			//std::cout << "Bulk string length out of range" << std::endl; //REDIS_ERR_PROTOCOL
			return REDIS_ERR;
		}
		if (len == -1) {
			// nil obj
			success = 1;
		}
		else {
			auto startidx = idx_ - 1;
			auto leftnum = data_len() - startidx;
			if (leftnum >= len + 2) {
				// string obj
				if (len > 0) {
					buff_.append(&data_[startidx], len);
					adjust_idx(len - 1);
				}
                obj = buff_;
				obj.type_ = vt;
				success = 1;
			}
		}
		if (success) {
			//std::cout << rds_types[vt] << len << " " << buff_ << std::endl;
			return REDIS_OK;
		}
		return REDIS_ERR;
	}

	inline int read_verb(std::int8_t vt, object& obj) {
		int success = 0;
		auto ret = read_num();
		if (ret < 0) {
			//std::cout << "read verb length fail." << std::endl;
			return REDIS_ERR;
		}
		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "verb format error." << std::endl;
			return REDIS_ERR;
		}
			
		auto len = std::stoll(buff_);
		buff_.clear();
		if (len < -1 || (LLONG_MAX > SIZE_MAX && len > (long long)SIZE_MAX)) {
			//std::cout << "Bulk string length out of range" << std::endl;
			return REDIS_ERR;
		}
		if (len == -1) {
			// nil obj
			success = 1;
		}
		else {
			auto startidx = idx_ - 1;
			obj.vstr_.append(&data_[startidx], 3);
			auto leftnum = data_len() - startidx;
			if (leftnum >= len + 2) {
				// string obj
				if (len > 4) {
					buff_.append(&data_[startidx+4], len-4);
					adjust_idx(len - 1);
				}
                obj = buff_;
				obj.type_ = vt;
				success = 1;
			}
		}
		if (success) {
			//std::cout << rds_types[vt] << len << " " << buff_ << std::endl;
			return REDIS_OK;
		}
		return REDIS_ERR;
	}

	inline int read_complex(std::int8_t vt, object& obj) {
		auto ret = read_num();
		if (ret < 0) {
			//std::cout << "read array length fail." << std::endl;
			return REDIS_ERR;
		}
		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "data format error." << std::endl;
			return REDIS_ERR;
		}
		auto elements = std::stoll(buff_);
		buff_.clear();
		if (elements < -1 || elements > INT_MAX) {
			//std::cout << "Multi-bulk length out of range" << std::endl;
			return REDIS_ERR;
		}

		//std::cout << rds_types[vt] << elements << std::endl;
		if (elements == -1) {
			// nil obj
		}
		else {
			if (vt == REDIS_TYPE_MAP) { // map obj
				//elements *= 2;
				std::unordered_map<std::string, object> map;
				for (auto idx = elements; idx > 0; --idx) {
					object tmpobj;
					auto ret = decode_t(tmpobj);
					if (ret == REDIS_ERR) {
						return REDIS_ERR;
					}
					std::string key = buff_;
					ret = decode_t(tmpobj);
					if (ret == REDIS_ERR) {
						return REDIS_ERR;
					}
					//map[key] = tmpobj;
					map.emplace(key, tmpobj);
				}
				obj = std::move(map);
			}
			else { // array obj
				std::vector<object> arr;
				for (auto idx = elements; idx > 0; --idx) {
					object tmpobj;
					auto ret = decode_t(tmpobj);
					if (ret == REDIS_ERR) {
						return REDIS_ERR;
					}
					arr.emplace_back(tmpobj);
				}
            	obj = std::move(arr);
			}
			
			obj.type_ = vt;
		}
		return REDIS_OK;
	}

	inline int read_nil(std::int8_t vt, object& obj) {
		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "nil format error." << std::endl;
			return REDIS_ERR;
		}

		obj.type_ = vt;
		obj.err_code_ = null_value;

		return REDIS_OK;
	}

	inline int read_double(std::int8_t vt, object& obj) {
		obj.type_ = vt;
		auto f = this->check_next('-');
		if (this->check_next('i') && this->check_next('n') && this->check_next('f')) {
			obj = f ? -INFINITY : INFINITY; // infinite
		}
		else if (this->check_next('n') && this->check_next('a') && this->check_next('n')) {
			obj = NAN; // nan
		} 
		else {
			auto ret = read_num();
			if (ret == REDIS_OK) {
				//std::cout << rds_types[vt] << buff_ << std::endl;
				double d = std::stod(buff_);
				obj = f ? -d : d;
				obj.type_ = vt;
			} else {
				return REDIS_ERR;
			}
		}

		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "double format error." << std::endl;
			return REDIS_ERR;
		}
		
		return REDIS_OK;
	}

	inline int read_bool(std::int8_t vt, object& obj) {
		if (this->check_next('t')) {
			obj = true;
		} else if (this->check_next('f')) {
			obj = false;
		} else {
			//std::cout << "bool format error." << std::endl;
			return REDIS_ERR;
		}

		obj.type_ = vt;

		if (!this->check_next('\r') || !this->check_next('\n')) {
			//std::cout << "bool format error." << std::endl;
			return REDIS_ERR;
		}
		
		return REDIS_OK;
	}

	inline int get_type() {
		int otype = REDIS_TYPE_NIL;
		switch (this->curchar_) {
		case '_':
			otype = REDIS_TYPE_NIL;
			break;
		case '$':
			otype = REDIS_TYPE_STRING;
			break;
		case '*':
			otype = REDIS_TYPE_ARRAY;
			break;
		case ':':
			otype = REDIS_TYPE_INTEGER;
			break;
		case '+':
			otype = REDIS_TYPE_STATUS;
			break;
		case '-':
			otype = REDIS_TYPE_ERROR;
			break;
		case ',':
			otype = REDIS_TYPE_DOUBLE;
			break; 
		case '#':
			otype = REDIS_TYPE_BOOL;
			break; 
		case '%':
			otype = REDIS_TYPE_MAP;
			break; 
		case '~':
			otype = REDIS_TYPE_SET;
			break; 
		case '>':
			otype = REDIS_TYPE_PUSH;
			break; 
		case '(':
			otype = REDIS_TYPE_BIGNUM;
			break; 
		case '=':
			otype = REDIS_TYPE_VERB;
			break; 
		default:
			otype = REDIS_TYPE_INVALID;
		}
		return otype;
	}
		
	int decode_t(object& obj) {
		buff_.clear();
		while (true) {
			switch (this->curchar_) {
			case '\n': case '\r': {
				inclinenum();
				break;
			}
			/*case ' ': case '\f': case '\t': case '\v': { 
				next();
				break;
			}*/
			case EOS: {
				return EOS;
			}
			default:
				auto vtype = get_type();
				next();
				switch (vtype) {
				case REDIS_TYPE_INVALID:
				case REDIS_TYPE_NIL:
					return read_nil(vtype, obj);
				case REDIS_TYPE_STRING:
					return read_long_str(vtype, obj);
				case REDIS_TYPE_ARRAY:
				case REDIS_TYPE_MAP:
				case REDIS_TYPE_SET:
				case REDIS_TYPE_PUSH:
					return read_complex(vtype, obj);
				case REDIS_TYPE_INTEGER:
					return read_integer(vtype, obj);
				case REDIS_TYPE_BIGNUM:
				case REDIS_TYPE_STATUS:
				case REDIS_TYPE_ERROR:
					return read_short_str(vtype, obj);
				case REDIS_TYPE_DOUBLE:
					return read_double(vtype, obj);
				case REDIS_TYPE_BOOL:
					return read_bool(vtype, obj);
				case REDIS_TYPE_VERB:
					return read_verb(vtype, obj);
				default:
					//assert(NULL);
					return REDIS_OK;
				}
			}
		}
		return REDIS_ERR;
	}
private:
	int idx_ = 0;
	const char* data_;
	int len_;

	std::string buff_;

	int curchar_ = EOS;
};


template<typename... Args>
inline void args_to_vec(std::vector<std::string>& vecs, Args&&... args) {
    (vecs.emplace_back(bnet::tool::to_string(std::forward<Args>(args))), ...);
}

template<typename... Args>
inline void pack_args(std::string& cmd, Args&&... args) {
    std::vector<std::string> vecs { bnet::tool::to_string(std::forward<Args>(args))... };
    resp_parse::encode(vecs, cmd);
}

//////////////////////// 测试 ////////////////////////////////////////////////////////////////////
inline void print_object(const object& obj) {
	//std::cout << "======================================" << std::endl;
	//auto vt = obj.index();
	if (obj.type_ <= REDIS_TYPE_INVALID || obj.type_ > REDIS_TYPE_VERB) {
		std::cout << "obj is invalid" << std::endl;
		return;
	}

	char chartype = rds_types[obj.type_];
	switch (obj.type_) {
	case REDIS_TYPE_NIL: {
		std::cout << chartype << "nil" << std::endl;
		break;
	}
	case REDIS_TYPE_STRING: 
	case REDIS_TYPE_BIGNUM:
	case REDIS_TYPE_STATUS: {
		std::string& str = obj;
		std::cout << chartype << str << std::endl;
		break;
	}
	case REDIS_TYPE_ERROR: {
		const std::string& str = obj.errmsg();
		std::cout << chartype << str << std::endl;
		break;
	}
	case REDIS_TYPE_INTEGER: {
		std::cout << chartype << (std::int64_t)obj << std::endl;
		break;
	}
    case REDIS_TYPE_DOUBLE: {
		std::cout << chartype << (double)obj << std::endl;
		break;
	}
	case REDIS_TYPE_BOOL: {
		std::cout << chartype << (bool)obj << std::endl;
		break;
	}
	case REDIS_TYPE_ARRAY:
	case REDIS_TYPE_SET:
	case REDIS_TYPE_PUSH: {
		std::vector<object>& arr = obj;
		auto count = arr.size();
		//if (obj.type_ == REDIS_TYPE_MAP) {
		//	count /= 2;
		//}
		std::cout << chartype << count << std::endl;
		for (auto& item : arr) {
			print_object(item);
		}
		break;
	}
	case REDIS_TYPE_MAP: {
		std::unordered_map<std::string, object>& map = obj;
		auto count = map.size();
		std::cout << chartype << count << std::endl;
		for (auto &&i : map) {
			std::cout << rds_types[REDIS_TYPE_STRING] << i.first << std::endl;
			print_object(i.second);
		}
		break;
	}
	default:
		std::cout << "obj is nil." << std::endl;
		return;
	}
}

inline void test_redis_parse() {
	std::string intstr(":123\r\n");
	std::string statusstr("+OK\r\n");
	std::string errstr("-ERR unknown command foobar\r\n");
	std::string longstr("$10\r\nfoobar adf\r\n");
	std::string longstr1("$0\r\n\r\n$-1\r\n");
	std::string arrstr("*-1\r\n*5\r\n:1\r\n:2\r\n:3\r\n:4\r\n$6\r\nfoobar\r\n");
	std::string arrstr1("*0\r\n*2\r\n*3\r\n:1\r\n:2\r\n:3\r\n*2\r\n+Foo\r\n-Bar\r\n$6\r\nfoobar\r\n");
	
	std::string boolstr("#t\r\n#f\r\n");
	std::string verbstr("=15\r\ntxt:Some string\r\n");
	std::string doublestr(",1.32\r\n,10\r\n,inf\r\n,-inf\r\n,nan\r\n,-123.001\r\n");
	std::string bignumstr("(3492890328409238509324850943850943825024385\r\n");
	std::string mapstr("%2\r\n+first\r\n:1\r\n+second\r\n:2\r\n");
	std::string setstr("~3\r\n:1\r\n:2\r\n,123.123\r\n");
	std::string pushstr(">3\r\n:1\r\n$10\r\nfoobar adf\r\n,123.123\r\n");

	std::string teststr(arrstr1 + longstr1 + longstr + errstr + intstr + statusstr + arrstr +
		boolstr + verbstr + doublestr + bignumstr + mapstr + setstr + pushstr);
	resp_parse rparse(teststr.c_str(), teststr.size());
	while (true) {
		auto objptr = std::make_shared<object>();
		auto ret = rparse.decode(*objptr);
		if (ret == REDIS_OK) {
			print_object(*objptr);
			std::cout << "========================================" << std::endl;
		}
		if (ret == EOS) {
			std::cout << "resp data parse finish." << std::endl;
			break;
		}
		if (ret == REDIS_ERR) {
			std::cout << "resp data parse fail." << std::endl;
			break;
		}
	}
}
}