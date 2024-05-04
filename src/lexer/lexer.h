#pragma once

#include "token.h"
#include <optional>

class Lexer {
private:
    TokenDef tokens[sizeof(TOKENS)/sizeof(*TOKENS)];
public:
    Lexer();

    const std::vector<Token> Tokenize(std::string input) const;
private:
    inline const std::optional<const TokenDef> match(const std::string & input) const;
    inline bool do_discard_token(const TokenId id) const;
};
