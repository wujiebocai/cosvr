// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#include <spdlog/details/file_helper.h>
#include <spdlog/details/null_mutex.h>
#include <spdlog/details/synchronous_factory.h>
#include <spdlog/sinks/base_sink.h>

#include <chrono>
#include <mutex>
#include <string>

#include "logutil.hpp"

namespace spdlog {
namespace sinks {
struct calc_filename_ret {
    filename_t old_filename_;
    filename_t new_filename_;
};

//
// Rotating file sink based on size
//
template <typename Mutex>
class blog_rotating_file_sink final : public base_sink<Mutex> {
public:
    blog_rotating_file_sink(filename_t base_filename,
                       std::size_t max_size,
                       std::size_t max_files,
                       bool rotate_on_open = false,
                       const file_event_handlers &event_handlers = {});
    filename_t calc_filename(const filename_t &filename, std::size_t index);
    calc_filename_ret calc_filename_target(const filename_t &filename, std::size_t index);
    filename_t filename();

protected:
    void sink_it_(const details::log_msg &msg) override;
    void flush_() override;

private:
    // Rotate files:
    // log.0.txt -> log.1.2024-04-25T20:44:10.txt
    // log.1.2024-04-25T20:44:10.txt -> log.2.2024-04-25T20:44:10.txt
    // log.2.2024-04-25T20:44:10.txt -> log.3.2024-04-25T20:44:10.txt
    // log.3.2024-04-25T20:44:10.txt -> delete
    void rotate_();

    // delete the target if exists, and rename the src file  to target
    // return true on success, false otherwise.
    bool rename_file_(const filename_t &src_filename, const calc_filename_ret &target_filename);

    filename_t base_filename_;
    std::size_t max_size_;
    std::size_t max_files_;
    std::size_t current_size_;
    details::file_helper file_helper_;

    std::unordered_map<std::size_t, filename_t> basenames_;
    filename_t filename_;
    filename_t ext_;
};

using blog_rotating_file_sink_mt = blog_rotating_file_sink<std::mutex>;
using blog_rotating_file_sink_st = blog_rotating_file_sink<details::null_mutex>;

}  // namespace sinks

//
// factory functions
//

template <typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<logger> blog_rotating_logger_mt(const std::string &logger_name,
                                                  const filename_t &filename,
                                                  size_t max_file_size,
                                                  size_t max_files,
                                                  bool rotate_on_open = false,
                                                  const file_event_handlers &event_handlers = {}) {
    return Factory::template create<sinks::blog_rotating_file_sink_mt>(
        logger_name, filename, max_file_size, max_files, rotate_on_open, event_handlers);
}

template <typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<logger> blog_rotating_logger_st(const std::string &logger_name,
                                                  const filename_t &filename,
                                                  size_t max_file_size,
                                                  size_t max_files,
                                                  bool rotate_on_open = false,
                                                  const file_event_handlers &event_handlers = {}) {
    return Factory::template create<sinks::blog_rotating_file_sink_st>(
        logger_name, filename, max_file_size, max_files, rotate_on_open, event_handlers);
}
}  // namespace spdlog

////////////////////////////////////////////////////////////////////////////////////
namespace spdlog {
namespace sinks {
tm now_tm() {
    auto tp = log_clock::now();
    time_t tnow = log_clock::to_time_t(tp);
    return spdlog::details::os::localtime(tnow);
}

template <typename Mutex>
SPDLOG_INLINE blog_rotating_file_sink<Mutex>::blog_rotating_file_sink(
    filename_t base_filename,
    std::size_t max_size,
    std::size_t max_files,
    bool rotate_on_open,
    const file_event_handlers &event_handlers)
    : base_filename_(std::move(base_filename)),
      max_size_(max_size),
      max_files_(max_files),
      file_helper_{event_handlers} {
    if (max_size == 0) {
        throw_spdlog_ex("rotating sink constructor: max_size arg cannot be zero");
    }

    if (max_files > 200000) {
        throw_spdlog_ex("rotating sink constructor: max_files arg cannot exceed 200000");
    }
    std::tie(filename_, ext_) = details::file_helper::split_by_extension(base_filename_);
    file_helper_.open(calc_filename(base_filename_, 0));
    current_size_ = file_helper_.size();  // expensive. called only once
    if (rotate_on_open && current_size_ > 0) {
        rotate_();
        current_size_ = 0;
    }

    get_all_log_filename(base_filename_, basenames_);
}

// calc filename according to index and file extension if exists.
// e.g. calc_filename("logs/mylog.txt, 3) => "logs/mylog.3.txt".
template <typename Mutex>
SPDLOG_INLINE filename_t blog_rotating_file_sink<Mutex>::calc_filename(const filename_t &filename,
                                                                  std::size_t index) {
    if (index == 0u) {
        return fmt_lib::format(SPDLOG_FILENAME_T("{}.{}{}"), filename_, index, ext_);
    }

    filename_t basename, ext;
    //std::tie(basename, ext) = details::file_helper::split_by_extension(filename);
    basename = basenames_[index];
    return fmt_lib::format(SPDLOG_FILENAME_T("{}.{}.{}{}"), filename_, index, basename, ext_);
}

// calc filename according to index and file extension if exists.
// e.g. calc_filename("logs/mylog.txt, 3) => "logs/mylog.3.txt".
template <typename Mutex>
SPDLOG_INLINE calc_filename_ret blog_rotating_file_sink<Mutex>::calc_filename_target(const filename_t &filename,
                                                                  std::size_t index) {
    //if (index == 0u) {
    //    return filename;
    //}

    filename_t basename, oldbasename;
    //std::tie(basename, ext) = details::file_helper::split_by_extension(filename);

    //if (auto itr = basenames_.find(index); itr != basenames_.end()) {
    //    oldbasename = itr->second; 
    //}
    if (index == 1) {
        auto tm = now_tm();
        basename = fmt_lib::format(SPDLOG_FMT_STRING(SPDLOG_FILENAME_T("{:04d}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}")),
                               tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                               tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    else {
        basename = basenames_[index-1];
    }

    oldbasename = basenames_[index];
    basenames_[index] = basename;

    return calc_filename_ret {
        old_filename_ : fmt_lib::format(SPDLOG_FILENAME_T("{}.{}.{}{}"), filename_, index, oldbasename, ext_),
        new_filename_ : fmt_lib::format(SPDLOG_FILENAME_T("{}.{}.{}{}"), filename_, index, basename, ext_)
    };
}

template <typename Mutex>
SPDLOG_INLINE filename_t blog_rotating_file_sink<Mutex>::filename() {
    std::lock_guard<Mutex> lock(base_sink<Mutex>::mutex_);
    return file_helper_.filename();
}

template <typename Mutex>
SPDLOG_INLINE void blog_rotating_file_sink<Mutex>::sink_it_(const details::log_msg &msg) {
    memory_buf_t formatted;
    base_sink<Mutex>::formatter_->format(msg, formatted);
    auto new_size = current_size_ + formatted.size();

    // rotate if the new estimated file size exceeds max size.
    // rotate only if the real size > 0 to better deal with full disk (see issue #2261).
    // we only check the real size when new_size > max_size_ because it is relatively expensive.
    if (new_size > max_size_) {
        file_helper_.flush();
        if (file_helper_.size() > 0) {
            rotate_();
            new_size = formatted.size();
        }
    }
    file_helper_.write(formatted);
    current_size_ = new_size;
}

template <typename Mutex>
SPDLOG_INLINE void blog_rotating_file_sink<Mutex>::flush_() {
    file_helper_.flush();
}

// Rotate files:
// log.0.txt -> log.1.2024-04-25T20:44:10.txt
// log.1.2024-04-25T20:44:10.txt -> log.2.2024-04-25T20:44:10.txt
// log.2.2024-04-25T20:44:10.txt -> log.3.2024-04-25T20:44:10.txt
// log.3.2024-04-25T20:44:10.txt -> delete
template <typename Mutex>
SPDLOG_INLINE void blog_rotating_file_sink<Mutex>::rotate_() {
    using details::os::filename_to_str;
    using details::os::path_exists;

    file_helper_.close();
    for (auto i = max_files_; i > 0; --i) {
        filename_t src = calc_filename(base_filename_, i - 1);
        if (!path_exists(src)) {
            continue;
        }
        auto target = calc_filename_target(base_filename_, i);

        if (!rename_file_(src, target)) {
            // if failed try again after a small delay.
            // this is a workaround to a windows issue, where very high rotation
            // rates can cause the rename to fail with permission denied (because of antivirus?).
            details::os::sleep_for_millis(100);
            if (!rename_file_(src, target)) {
                file_helper_.reopen(
                    true);  // truncate the log file anyway to prevent it to grow beyond its limit!
                current_size_ = 0;
                throw_spdlog_ex("blog_rotating_file_sink: failed renaming " + filename_to_str(src) +
                                    " to " + filename_to_str(target.new_filename_),
                                errno);
            }
        }
    }
    file_helper_.reopen(true);
}

// delete the target if exists, and rename the src file  to target
// return true on success, false otherwise.
template <typename Mutex>
SPDLOG_INLINE bool blog_rotating_file_sink<Mutex>::rename_file_(const filename_t &src_filename,
                                                           const calc_filename_ret &target_filename) {
    // try to delete the target file in case it already exists.
    (void)details::os::remove(target_filename.old_filename_);
    return details::os::rename(src_filename, target_filename.new_filename_) == 0;
}

}  // namespace sinks
}  // namespace spdlog

