#pragma once

#include "token.h"
#include <neonc.h>

class Lexer {
public:
    Lexer() = default;

    const std::vector<Token> Tokenize(std::string input) const;
};
