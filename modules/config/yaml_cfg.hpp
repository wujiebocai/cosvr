#pragma once

#include <yaml-cpp/yaml.h>

namespace modules {
namespace cfg {
template <typename T>
concept has_load_func  = requires(T t) {
    { t.load(YAML::Node{}) } -> std::same_as<bool>;
};

template<typename T>
void from_yaml(const YAML::Node& node, const std::string& filed, T& t) {
    const auto& nd = node[filed];
    if (!nd.IsDefined()) {
        std::cout << "field [" << filed << "] not defined, use default value" << std::endl;
        return;
    }

    auto type = nd.Type();
    bool flag = false;
    if constexpr (has_load_func<T>) { 
        if (type == YAML::NodeType::value::Map) {
#ifdef YAML_DEBUG
            std::cout << filed << ":" << std::endl;
#endif
            t.load(nd);
            flag = true;
        }
    } else { 
        if (type == YAML::NodeType::value::Scalar) {
            t = nd.as<T>();  
            flag = true;
#ifdef YAML_DEBUG
            std::cout << filed << ": " << t << std::endl;
#endif
        }
    }

    if (!flag) {
        // throw std::runtime_error("Failed to load field: " + filed);
        std::cerr << "field [" << filed << "] type error. type: " << type << std::endl;
    }
}

template<typename T>
void from_yaml(const YAML::Node& node, const std::string& filed, std::vector<T>& ts) {
    const auto& nd = node[filed];
    if (!nd.IsDefined()) {
        std::cout << "field [" << filed << "] not defined, use default value" << std::endl;
        return;
    }

    auto type = nd.Type();
    if (type != YAML::NodeType::value::Sequence) {
        // throw std::runtime_error("Failed to load field: " + filed);
        std::cerr << "field [" << filed << "] type error. type: " << type << std::endl;
        return;
    }

#ifdef YAML_DEBUG
    std::cout << filed << ": " << std::endl;
#endif

    if constexpr (has_load_func<T>) { 
        for (auto itr : nd) {
            T t;
            t.load(itr);
            ts.push_back(t);
        }
    } else { 
        ts = nd.as<std::vector<T>>();
#ifdef YAML_DEBUG
        for (auto &i : ts) {
            std::cout << "  " << i << std::endl;
        }
#endif
    }
}

template<typename T>
void from_yaml(const YAML::Node& node, const std::string& filed, std::unordered_map<std::string, T>& ts) {
    const auto& nd = node[filed];
    if (!nd.IsDefined()) {
        std::cout << "field [" << filed << "] not defined, use default value" << std::endl;
        return;
    }

    auto type = nd.Type();
    if (type != YAML::NodeType::value::Map) {
        // throw std::runtime_error("Failed to load field: " + filed);
        std::cerr << "field [" << filed << "] type error. type: " << type << std::endl;
        return;
    }

#ifdef YAML_DEBUG
    std::cout << filed << ": " << std::endl;
#endif

    if constexpr (has_load_func<T>) { 
        for (auto itr : nd) {
#ifdef YAML_DEBUG
            std::cout << itr.first.as<std::string>() << ":" << std::endl;
#endif
            T t;
            t.load(itr.second);
            ts[itr.first.as<std::string>()] = t;
        }
    } else { 
        ts = nd.as<std::unordered_map<std::string, T>>();
#ifdef YAML_DEBUG
        for (auto &i : ts) {
            std::cout << "  " << i.first << ": " << i.second << std::endl;
        }
#endif
    }
}

template<typename T>
bool load_config(const std::string& filepath, T&& t) {
    try {
        YAML::Node rnode = YAML::LoadFile(filepath);
        if (rnode.IsNull()) {
            return false;
        }

        std::cout << "yaml config filepath: " << filepath << std::endl;
        t.load(rnode);
        return true;
    }
    catch (std::exception& e) { 
        std::cerr << "load yaml config fail, filepath: " << filepath << " errmsg: " << e.what() << std::endl;
    }
    return false;
}

}   // namespace cfg
}   // namespace modules

#define _YAML_VAL(val) modules::cfg::from_yaml(node, #val, val);
#define _YAML_PARAM0()
#define _YAML_PARAM1(val) _YAML_VAL(val)
#define _YAML_PARAM2(val, ...) _YAML_VAL(val) _YAML_PARAM1(__VA_ARGS__)
#define _YAML_PARAM3(val, ...) _YAML_VAL(val) _YAML_PARAM2(__VA_ARGS__)
#define _YAML_PARAM4(val, ...) _YAML_VAL(val) _YAML_PARAM3(__VA_ARGS__)
#define _YAML_PARAM5(val, ...) _YAML_VAL(val) _YAML_PARAM4(__VA_ARGS__)
#define _YAML_PARAM6(val, ...) _YAML_VAL(val) _YAML_PARAM5(__VA_ARGS__)
#define _YAML_PARAM7(val, ...) _YAML_VAL(val) _YAML_PARAM6(__VA_ARGS__)
#define _YAML_PARAM8(val, ...) _YAML_VAL(val) _YAML_PARAM7(__VA_ARGS__)
#define _YAML_PARAM9(val, ...) _YAML_VAL(val) _YAML_PARAM8(__VA_ARGS__)
#define _YAML_PARAM10(val, ...) _YAML_VAL(val) _YAML_PARAM9(__VA_ARGS__)
#define _YAML_PARAM11(val, ...) _YAML_VAL(val) _YAML_PARAM10(__VA_ARGS__)
#define _YAML_PARAM12(val, ...) _YAML_VAL(val) _YAML_PARAM11(__VA_ARGS__)
#define _YAML_PARAM13(val, ...) _YAML_VAL(val) _YAML_PARAM12(__VA_ARGS__)
#define _YAML_PARAM14(val, ...) _YAML_VAL(val) _YAML_PARAM13(__VA_ARGS__)
#define _YAML_PARAM15(val, ...) _YAML_VAL(val) _YAML_PARAM14(__VA_ARGS__)
#define _YAML_PARAM16(val, ...) _YAML_VAL(val) _YAML_PARAM15(__VA_ARGS__)
#define _YAML_PARAM17(val, ...) _YAML_VAL(val) _YAML_PARAM16(__VA_ARGS__)
#define _YAML_PARAM18(val, ...) _YAML_VAL(val) _YAML_PARAM17(__VA_ARGS__)
#define _YAML_PARAM19(val, ...) _YAML_VAL(val) _YAML_PARAM18(__VA_ARGS__)
#define _YAML_PARAM20(val, ...) _YAML_VAL(val) _YAML_PARAM19(__VA_ARGS__)
#define _YAML_PARAM21(val, ...) _YAML_VAL(val) _YAML_PARAM20(__VA_ARGS__)
#define _YAML_PARAM22(val, ...) _YAML_VAL(val) _YAML_PARAM21(__VA_ARGS__)
#define _YAML_PARAM23(val, ...) _YAML_VAL(val) _YAML_PARAM22(__VA_ARGS__)
#define _YAML_PARAM24(val, ...) _YAML_VAL(val) _YAML_PARAM23(__VA_ARGS__)
#define _YAML_PARAM25(val, ...) _YAML_VAL(val) _YAML_PARAM24(__VA_ARGS__)
#define _YAML_PARAM26(val, ...) _YAML_VAL(val) _YAML_PARAM25(__VA_ARGS__)
#define _YAML_PARAM27(val, ...) _YAML_VAL(val) _YAML_PARAM26(__VA_ARGS__)
#define _YAML_PARAM28(val, ...) _YAML_VAL(val) _YAML_PARAM27(__VA_ARGS__)
#define _YAML_PARAM29(val, ...) _YAML_VAL(val) _YAML_PARAM28(__VA_ARGS__)
#define _YAML_PARAM30(val, ...) _YAML_VAL(val) _YAML_PARAM29(__VA_ARGS__)
#define _YAML_PARAM31(val, ...) _YAML_VAL(val) _YAML_PARAM30(__VA_ARGS__)
#define _YAML_PARAM32(val, ...) _YAML_VAL(val) _YAML_PARAM31(__VA_ARGS__)
#define _YAML_PARAM33(val, ...) _YAML_VAL(val) _YAML_PARAM32(__VA_ARGS__)
#define _YAML_PARAM34(val, ...) _YAML_VAL(val) _YAML_PARAM33(__VA_ARGS__)
#define _YAML_PARAM35(val, ...) _YAML_VAL(val) _YAML_PARAM34(__VA_ARGS__)
#define _YAML_PARAM36(val, ...) _YAML_VAL(val) _YAML_PARAM35(__VA_ARGS__)
#define _YAML_PARAM37(val, ...) _YAML_VAL(val) _YAML_PARAM36(__VA_ARGS__)
#define _YAML_PARAM38(val, ...) _YAML_VAL(val) _YAML_PARAM37(__VA_ARGS__)
#define _YAML_PARAM39(val, ...) _YAML_VAL(val) _YAML_PARAM38(__VA_ARGS__)
#define _YAML_PARAM40(val, ...) _YAML_VAL(val) _YAML_PARAM39(__VA_ARGS__)
#define _YAML_PARAM41(val, ...) _YAML_VAL(val) _YAML_PARAM40(__VA_ARGS__)
#define _YAML_PARAM42(val, ...) _YAML_VAL(val) _YAML_PARAM41(__VA_ARGS__)
#define _YAML_PARAM43(val, ...) _YAML_VAL(val) _YAML_PARAM42(__VA_ARGS__)
#define _YAML_PARAM44(val, ...) _YAML_VAL(val) _YAML_PARAM43(__VA_ARGS__)
#define _YAML_PARAM45(val, ...) _YAML_VAL(val) _YAML_PARAM44(__VA_ARGS__)
#define _YAML_PARAM46(val, ...) _YAML_VAL(val) _YAML_PARAM45(__VA_ARGS__)
#define _YAML_PARAM47(val, ...) _YAML_VAL(val) _YAML_PARAM46(__VA_ARGS__)
#define _YAML_PARAM48(val, ...) _YAML_VAL(val) _YAML_PARAM47(__VA_ARGS__)
#define _YAML_PARAM49(val, ...) _YAML_VAL(val) _YAML_PARAM48(__VA_ARGS__)
#define _YAML_PARAM50(val, ...) _YAML_VAL(val) _YAML_PARAM49(__VA_ARGS__)
#define _YAML_PARAM51(val, ...) _YAML_VAL(val) _YAML_PARAM50(__VA_ARGS__)
#define _YAML_PARAM52(val, ...) _YAML_VAL(val) _YAML_PARAM51(__VA_ARGS__)
#define _YAML_PARAM53(val, ...) _YAML_VAL(val) _YAML_PARAM52(__VA_ARGS__)
#define _YAML_PARAM54(val, ...) _YAML_VAL(val) _YAML_PARAM53(__VA_ARGS__)
#define _YAML_PARAM55(val, ...) _YAML_VAL(val) _YAML_PARAM54(__VA_ARGS__)
#define _YAML_PARAM56(val, ...) _YAML_VAL(val) _YAML_PARAM55(__VA_ARGS__)
#define _YAML_PARAM57(val, ...) _YAML_VAL(val) _YAML_PARAM56(__VA_ARGS__)
#define _YAML_PARAM58(val, ...) _YAML_VAL(val) _YAML_PARAM57(__VA_ARGS__)
#define _YAML_PARAM59(val, ...) _YAML_VAL(val) _YAML_PARAM58(__VA_ARGS__)
#define _YAML_PARAM60(val, ...) _YAML_VAL(val) _YAML_PARAM59(__VA_ARGS__)
#define _YAML_PARAM61(val, ...) _YAML_VAL(val) _YAML_PARAM60(__VA_ARGS__)
#define _YAML_PARAM62(val, ...) _YAML_VAL(val) _YAML_PARAM61(__VA_ARGS__)
#define _YAML_PARAM63(val, ...) _YAML_VAL(val) _YAML_PARAM62(__VA_ARGS__)
#define _YAML_PARAM64(val, ...) _YAML_VAL(val) _YAML_PARAM63(__VA_ARGS__)

#define _YAML_OVERRIDED(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,      \
                        _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31,  \
                        _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,  \
                        _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61,  \
                        _62, _63, _64, _65, N, ...)                                                 \
                        N

#define YAML_ALL_PARAM(...) \
    _YAML_OVERRIDED("", ##__VA_ARGS__, \
    _YAML_PARAM64, \
    _YAML_PARAM63, _YAML_PARAM62, \
    _YAML_PARAM61, _YAML_PARAM60, \
    _YAML_PARAM59, _YAML_PARAM58, \
    _YAML_PARAM57, _YAML_PARAM56, \
    _YAML_PARAM55, _YAML_PARAM54, \
	_YAML_PARAM53, _YAML_PARAM52, \
	_YAML_PARAM51, _YAML_PARAM50, \
    _YAML_PARAM49, _YAML_PARAM48, \
    _YAML_PARAM47, _YAML_PARAM46, \
    _YAML_PARAM45, _YAML_PARAM44, \
	_YAML_PARAM43, _YAML_PARAM42, \
	_YAML_PARAM41, _YAML_PARAM40, \
    _YAML_PARAM39, _YAML_PARAM38, \
    _YAML_PARAM37, _YAML_PARAM36, \
    _YAML_PARAM35, _YAML_PARAM34, \
	_YAML_PARAM33, _YAML_PARAM32, \
	_YAML_PARAM31, _YAML_PARAM30, \
    _YAML_PARAM29, _YAML_PARAM28, \
    _YAML_PARAM27, _YAML_PARAM26, \
    _YAML_PARAM25, _YAML_PARAM24, \
	_YAML_PARAM23, _YAML_PARAM22, \
	_YAML_PARAM21, _YAML_PARAM20, \
    _YAML_PARAM19, _YAML_PARAM18, \
    _YAML_PARAM17, _YAML_PARAM16, \
    _YAML_PARAM15, _YAML_PARAM14, \
	_YAML_PARAM13, _YAML_PARAM12, \
	_YAML_PARAM11, _YAML_PARAM10, \
    _YAML_PARAM9, _YAML_PARAM8, \
    _YAML_PARAM7, _YAML_PARAM6, \
    _YAML_PARAM5, _YAML_PARAM4, \
	_YAML_PARAM3, _YAML_PARAM2, \
	_YAML_PARAM1, _YAML_PARAM0) \
	(__VA_ARGS__)

    