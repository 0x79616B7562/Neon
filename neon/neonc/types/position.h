#pragma once

#include <neonc.h>

namespace neonc {
    struct Position {
        Position(const uint64_t line, const uint64_t column): line(line), column(column) {}

        std::string string() const;

        uint64_t line;
        uint64_t column;
    };
}
