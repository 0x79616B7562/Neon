#include "grammar.h"

std::optional<Token> parse_token(Pack * pack, TokenId to_find, std::optional<TokenId> ignore) {
    for (int i = pack->index; i < std::size(pack->tokens); i++) {
        Token tok = pack->tokens[i];
   
        if (tok.token == to_find) {
            pack->index += i - pack->index + 1;

            return tok;
        }

        if (ignore.has_value()) {
            if (ignore.value() == tok.token) {
                continue;
            }
        }

        return {};
    }

    return {};
}

// 'fn' 'ident' '(' ')' '{' '}'
bool parse_function(Pack * pack, Node * node) {
    if (!parse_token(pack, TokenId::FN, TokenId::NEWLINE))
        return false;

    auto ident = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
    if (!ident) return false;
    
    if (!parse_token(pack, TokenId::LPAREN, TokenId::NEWLINE)) return false;
    if (!parse_token(pack, TokenId::RPAREN, TokenId::NEWLINE)) return false;
    
    if (!parse_token(pack, TokenId::LBRACE, TokenId::NEWLINE)) return false;
    if (!parse_token(pack, TokenId::RBRACE, TokenId::NEWLINE)) return false;

    return true;
}
