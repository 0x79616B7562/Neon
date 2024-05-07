#include "grammar.h"

#define CHECK_RET_FALSE(val) if (!val) { return false; }
#define CHECK_RET_FALSE_ERR(val, pck, error) if (!val) { \
    throw_parse_error(pck, error); \
    return false; }

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

// EXPR = num
bool parse_expr(Pack * pack, Node * node) {
    return parse_token(pack, TokenId::NUM, TokenId::NEWLINE).has_value();
}

// VARIABLE = 'let' 'mut'? 'ident' ((':' 'ident') | (':' 'ident')? ('=' EXPR)) ('\n' | ';')
bool parse_variable(Pack * pack, Node * node) {
    auto lettok = parse_token(pack, TokenId::LET, TokenId::NEWLINE);
    CHECK_RET_FALSE(lettok)

    auto mut_tok = parse_token(pack, TokenId::MUT, TokenId::NEWLINE);
    
    auto ident = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
    CHECK_RET_FALSE_ERR(ident, pack, "expected identifier")
    
    auto variable = Node(AstId::VARIABLE, {Data(DataId::IDENTIFIER, ident->value, {{lettok->line, lettok->column}})});
    if (mut_tok) variable.data.push_back(Data(DataId::MUTABLE, {}, {{mut_tok->line, mut_tok->column}}));

    if (parse_token(pack, TokenId::COLON, TokenId::NEWLINE)) {
        auto _type = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
        CHECK_RET_FALSE_ERR(_type, pack, "expected type")

        variable.data.push_back(Data(DataId::TYPE, _type->value, {{_type->line, _type->column}}));

        if (parse_token(pack, TokenId::EQUALS, TokenId::NEWLINE)) {
            CHECK_RET_FALSE_ERR(parse_expr(pack, node), pack, "expected expression")
        }
    } else {
        CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::EQUALS, TokenId::NEWLINE), pack, "expected '='")
        CHECK_RET_FALSE_ERR(parse_expr(pack, node), pack, "expected expression")
    }

    if (!parse_token(pack, TokenId::NEWLINE, {}))
        CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::SEMICOLON, {}), pack, "expected newline or semicolon")

    node->nodes.push_back(variable);

    return true;
}

// BODY = VARIABLE
bool parse_body(Pack * pack, Node * node) {
    return parse_variable(pack, node);
}

// FUNCTION = 'fn' 'ident' '(' ')' '{' BODY*? '}'
bool parse_function(Pack * pack, Node * node) {
    auto fntok = parse_token(pack, TokenId::FN, TokenId::NEWLINE);
    CHECK_RET_FALSE_ERR(fntok, pack, "expected 'fn'")

    auto ident = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
    CHECK_RET_FALSE_ERR(ident, pack, "expected identifier")

    auto fnnode = Node(AstId::FUNCTION, {Data(DataId::IDENTIFIER, ident->value, {{fntok->line, fntok->column}})});

    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::LPAREN, TokenId::NEWLINE), pack, "expected '('")
    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::RPAREN, TokenId::NEWLINE), pack, "expected ')'")

    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::LBRACE, TokenId::NEWLINE), pack, "expected '{'")

    while (parse_body(pack, &fnnode));

    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::RBRACE, TokenId::NEWLINE), pack, "expected '}'")

    node->nodes.push_back(fnnode);

    return true;
}
