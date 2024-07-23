#pragma once

#include "error/error.hpp"

// 错误处理机制

ERR_ENUM_CATEGORY_BEGIN(tsterr, 
    /* error */
    ERR_TST_1 = 1, 
    ERR_TST_2, 
    ERR_TST_3
)

// errcode, errmsg
ERR_ENTRY(ERR_TST_1, "err one")
ERR_ENTRY(ERR_TST_2, "err tow")
ERR_ENTRY(ERR_TST_3, "err three")
ERR_ENUM_CATEGORY_END(tsterr)
ERR_STD_CODE_ENUM(DEFUALT_NAMESPACE, tsterr)

void test_err() {
    auto err = modules::wrap_error(ERR_TST_1, "wrap err code {}", "test error");
    std::cerr << "err code: " << err.value() << ", err msg: " << err.message() << std::endl;

    std::error_code ec = ERR_TST_1; //make_error_code(ERR_TST_1);
    err = modules::wrap_error(ec, "wrap std::error_code {}", "test error");
    std::cerr << "err code: " << err.value() << ", err msg: " << err.message() << std::endl;

    err = modules::wrap_error(err, "wrap error {}", "test error");
    std::cerr << "err code: " << err.value() << ", err msg: " << err.message() << std::endl;

    /*
     带堆栈信息的错误信息，方便错误定位，便于调试问题:
        err code: 1, msg: wrap err code with stack info test error; call stack: 
        #0 /home/.../modules/error/error.hpp:139 wrap_error_with_stack<char const (&)[11]> [6925190]
        #1 /home/.../demo/error.hpp:38 test_err [5333590]
        #2 /home/.../cosvr/demo/main.cpp:688 main [5389161]
        #3 ../csu/libc-start.c:308 __libc_start_main [140737347588226]
        #4 :0 _start [4302237]
        #5 :0  [18446744073709551615]
    */
    err = modules::wrap_error_with_stack(ERR_TST_1, "wrap err code with stack info {}", "test error");
    std::cerr << "err code: " << err.value() << ", err msg: " << err.message() << std::endl;

    ec = ERR_TST_2;
    err = modules::wrap_error_with_stack(ec, "wrap std::error_code with stack info {}", "test error");
    std::cerr << "err code: " << err.value() << ", err msg: " << err.message() << std::endl;

    err = modules::wrap_error_with_stack(err, "wrap error with stack info {}", "test error");
    std::cerr << "err code: " << err.value() << ", err msg: " << err.message() << std::endl;
}