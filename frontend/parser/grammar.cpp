#include "grammar.h"

#define CHECK_RET_FALSE(val) if (!val) return false

const std::optional<Token> parse_token(Pack * pack, const TokenId to_find, const std::optional<TokenId> ignore) {
    for (std::size_t i = pack->index; i < std::size(pack->tokens); i++) {
        Token tok = pack->tokens[i];

        if (tok.token == to_find) {
            pack->index += i - pack->index + 1;
            
            return tok;
        }

        if (ignore.has_value())
            if (ignore.value() == tok.token)
                continue;

        return {};
    }

    return {};
}

// BODY =
bool parse_body(Pack * pack, Node * node) {
    return false;
}

// FUNCTION = 'fn' 'ident' '(' ')' '{' BODY*? '}'
bool parse_function(Pack * pack, Node * node) {
    auto fntok = parse_token(pack, TokenId::FN, TokenId::NEWLINE);
    CHECK_RET_FALSE(fntok);

    auto ident = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
    CHECK_RET_FALSE(ident);

    auto fnnode = Node(Data(AstId::FUNCTION, ident->value, {{fntok->line, fntok->column}}));

    CHECK_RET_FALSE(parse_token(pack, TokenId::LPAREN, TokenId::NEWLINE));
    CHECK_RET_FALSE(parse_token(pack, TokenId::RPAREN, TokenId::NEWLINE));

    CHECK_RET_FALSE(parse_token(pack, TokenId::LBRACE, TokenId::NEWLINE));

    while (parse_body(pack, &fnnode));

    CHECK_RET_FALSE(parse_token(pack, TokenId::RBRACE, TokenId::NEWLINE));

    node->nodes.push_back(fnnode);

    return true;
}
