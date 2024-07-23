#pragma once

#include "util/backward.hpp"

namespace modules::err {
// 获取调用栈信息
inline std::string get_stack_info(size_t depth = 16) {
    constexpr size_t start_idx = 3;

    std::string stack_info;
    if (depth == 0) return stack_info;
    depth += start_idx;

    StackTrace st; st.load_here(depth);
    TraceResolver tr; tr.load_stacktrace(st);

    stack_info = "call stack: \r\n";
    auto stlen = st.size();
    for (size_t i = start_idx; i < stlen; ++i) {
	    ResolvedTrace trace = tr.resolve(st[i]);
        stack_info += "#" + std::to_string(i - start_idx);
        stack_info += " " + trace.source.filename;
        stack_info += ":" + std::to_string(trace.source.line);
        stack_info += " " + trace.source.function;
        stack_info += " [" + std::to_string(uint64_t(trace.addr)) + "]";
        if (i < stlen - 1) stack_info += "\r\n";

	    //std::cout << "#" << i
		//    << " " << trace.object_filename
		//    << " " << trace.object_function
		//    << " [" << trace.addr << "]"
	    //<< std::endl;
    }

    return stack_info;
}
}