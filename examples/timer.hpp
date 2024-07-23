#pragma once

#include <iostream> 
#include "timer/timer.hpp"
#include "timer/logic_timer.hpp"

// 计时器本身不是线程安全的
// 千万量级计时器，占用cpu及内存都极低，所以计时器可以单独创建一个actor来跑，然后和其他actor进行通信；也可以集成到其他actor中跑.

void print_cur_time(std::string str = "") {
    time_t currentTime = time(0);
    struct tm* localTime = localtime(&currentTime);
    std::cout << str << ";  当前时间为: "
              << localTime->tm_year + 1900 << "-"
              << localTime->tm_mon + 1 << "-"
              << localTime->tm_mday << " "
              << localTime->tm_hour << ":"
              << localTime->tm_min << ":"
              << localTime->tm_sec << std::endl;
}

void test_timer() {
    // timer
    auto exe = modules::get_global_executor();
    static modules::timer::timer timer(exe->context());
    timer.loop(60 * 1000, []() mutable { 
        print_cur_time("60s loop"); 
        return true;
    });

    timer.after(60 * 1000, []() mutable { 
        print_cur_time("60s after"); 
        return true;
    });

    // logic timer
    auto exe1 = modules::get_global_executor();
    static modules::timer::logic_timer logictimer(exe1->context());

    // alarm接口的用法与loop_alarm是一样的，只是不会loop
    logictimer.loop_alarm([]()mutable { print_cur_time("loop_alarm 每分钟第10秒闹钟回调"); }, 10);
    logictimer.loop_alarm([]()mutable { print_cur_time("loop_alarm 每小时第3分钟，第10秒闹钟回调"); }, 3, 10);
    logictimer.loop_alarm([]()mutable { print_cur_time("loop_alarm 每天8点3分10秒闹钟回调"); }, 8, 3, 10);
    logictimer.loop_alarm([]()mutable { print_cur_time("loop_alarm 每月1号9点3分10秒闹钟回调"); }, 1, 9, 3, 10);
    logictimer.loop_alarm([]()mutable { print_cur_time("loop_alarm 每年9月23号9点16分钟10秒闹钟回调"); }, 9, 23, 9, 16, 10);

    logictimer.loop(60 * 1000, []() mutable { 
        print_cur_time("60s loop"); 
        return true;
    });

    logictimer.after(60 * 1000, []() mutable { 
        print_cur_time("60s after"); 
        return true;
    });
}

