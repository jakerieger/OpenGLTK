// Author: Jake Rieger
// Created: 9/23/2024.
//

#pragma once

#include <cstdio>
#include <cstdlib>
#include <source_location>

[[noreturn]] inline void Panic(const char* msg,
                               const std::source_location& loc = std::source_location::current()) {
    fprintf(stderr,
            "%s:%d\nPANIC: \n  In: %s\n  Error: %s\n",
            loc.file_name(),
            loc.line(),
            loc.function_name(),
            msg);
    std::abort();
}