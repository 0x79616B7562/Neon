#pragma once

#include "../lexer/token.h"
#include <cstdint>
#include <vector>

struct Pack {
    uint32_t index = 0;
    const std::vector<Token> tokens;

    Pack(std::vector<Token> tokens) : tokens(tokens) {}

    Token get() const;
    bool is_at_end() const;
    void next();
};
