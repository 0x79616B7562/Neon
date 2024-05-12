#pragma once

#include "../util/clicolor.h"
#include "../types/tokenid.h"
#include "tokens.h"
#include <neonc.h>

struct TokenDef {
    TokenId token;
    char * match;
    bool do_discard;
    bool is_regex;

    std::regex regex;
};

struct Token {
    void dump() const;

    const TokenId token;
    const std::string value;

    const uint32_t line;
    const uint32_t column;
};
