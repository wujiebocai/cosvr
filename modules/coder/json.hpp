#pragma once

#include <string_view>
#include <json.hpp>

namespace modules {
struct json_coder {
    static bool deserialize(nlohmann::json& js, std::string_view buffer) {
        js = nlohmann::json::parse(buffer);
        return true;
    }

    static bool serialize(const nlohmann::json& js, std::string& buffer) {
        buffer = js.dump();
        return true;
    }
};

}