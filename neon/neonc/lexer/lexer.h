#pragma once

#include "token.h"
#include <neonc.h>

class Lexer {
public:
    Lexer();

    const std::vector<Token> Tokenize(std::string input) const;
private:
    inline const std::optional<const TokenDef> match(const std::string input) const;
    inline bool do_discard_token(const TokenId id) const;
private:
    TokenDef tokens[sizeof(TOKENS)/sizeof(*TOKENS)];
};
