#pragma once

#include "../lexer/token.h"
#include <cstdint>
#include <vector>

struct Pack {
    Pack(const std::string file_name, std::vector<Token> tokens) : file_name(file_name), tokens(tokens) {}

    const std::string file_name;
    Token get() const;
    Token get_next() const;
    bool is_at_end() const;
    void next();
    
    uint32_t index = 0;
    const std::vector<Token> tokens;
};
