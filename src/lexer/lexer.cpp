#include "lexer.h"
#include "token.h"
#include <cstdio>
#include <vector>

Lexer::Lexer() {
}

std::vector<Token> Lexer::Tokenize(std::string input) {
    std::vector<Token> tokens;

    for (int i = 0; i < input.length(); i++) {
        char ch = input[i];
    }

    return tokens;
}
