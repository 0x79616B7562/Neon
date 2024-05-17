#pragma once

#include "../util/clicolor.h"
#include "../types/tokenid.h"
#include <neonc.h>

struct Token {
    void dump() const;

    const TokenId token;
    const std::string value;

    const uint64_t line;
    const uint64_t column;
};
