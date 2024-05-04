#pragma once

#include "../util/clicolor.h"
#include "../types/tokenid.h"
#include "tokens.h"
#include <cstdint>
#include <regex>
#include <iostream>

struct TokenDef {
    TokenId token;
    char * match;
    bool do_discard;
    bool is_regex;

    std::regex regex;
};

struct Token {
    const TokenId token;
    const std::string value;

    const uint32_t line;
    const uint32_t column;

    void dump() const;
};
