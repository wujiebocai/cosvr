#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <spdlog/common.h>

namespace spdlog::sinks {
SPDLOG_INLINE void get_file_info(const std::string& filename, std::vector<std::string>& tokens) {
    size_t startPos = 0;
    for (size_t i = 0; i < filename.size(); ++i) {
        if (filename[i] == '.') {
            tokens.emplace_back(filename.substr(startPos, i - startPos));
            startPos = i + 1;
        }
    }

    //tokens.emplace_back(filename.substr(startPos));
}

SPDLOG_INLINE void get_all_log_filename(const std::string& filepath, std::unordered_map<std::size_t, spdlog::filename_t>& files) {
    namespace fs = std::filesystem;
    fs::path fullPath(filepath);
    std::string dirpath = fullPath.parent_path().string();

    std::vector<std::string> tokens;
    if (fs::exists(dirpath) && fs::is_directory(dirpath)) {
        for (const auto& entry : fs::directory_iterator(dirpath)) {
            if (fs::is_regular_file(entry.path())) {
                tokens.clear();
                get_file_info(entry.path().string(), tokens);
                //std::cout << entry.path().filename().string() << std::endl;
                if (tokens.size() == 3) {
                    auto idx = std::stoll(tokens[1]);
                    auto basename = tokens[2];
                    files[idx] = basename;
                }
            }
        }
    } else {
        //std::cout << "Directory doesn't exist or is not a valid directory path." << std::endl;
    }
}

}