// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include <cstdio>
#include <cstdlib>
#include <source_location>

constexpr std::source_location GetSourceLocation() {
    return std::source_location::current();
}

[[noreturn]] inline void Panic(const char* msg,
                               const std::source_location& loc = GetSourceLocation()) {
    fprintf(stderr,
            "%s:%d\nPANIC: \n  In: %s\n  Error: %s\n",
            loc.file_name(),
            loc.line(),
            loc.function_name(),
            msg);
    std::abort();
}

template<typename... Args>
inline void Panic(const std::source_location& loc,
                  const std::format_string<std::type_identity_t<Args>...>& fmt,
                  Args&&... args) {
    auto str = std::format(fmt, std::forward<Args>(args)...);
    Panic(str.c_str(), loc);
}