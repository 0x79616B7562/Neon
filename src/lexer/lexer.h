#pragma once

#include "token.h"
#include <string>
#include <vector>
#include <stdio.h>

class Lexer {
public:
    Lexer();

    std::vector<Token> Tokenize(std::string input);
};
