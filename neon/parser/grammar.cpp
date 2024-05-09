#include "grammar.h"

#define CHECK_RET_FALSE(val) if (!val) { return false; }
#define CHECK_RET_FALSE_ERR(val, pck, error) if (!val) { throw_parse_error(pck, error); return false; }

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

// NUM = 'num'
bool parse_num(Pack * pack, Node * node) {
    auto num = parse_token(pack, TokenId::NUM, TokenId::NEWLINE);

    if (num) {
        node->nodes.push_back(Node(AstId::NUMBER, num->value, {{num->line, num->column}}));

        return true;
    }

    return false;
}

// EXPR = NUM
bool parse_expr(Pack * pack, Node * node) {
    auto expr = Node(AstId::EXPRESSION, {}, {});

    if (parse_num(pack, &expr)) {
        node->nodes.push_back(expr);

        return true;
    }

    return false;
}

// VARIABLE = 'let' 'mut'? 'ident' ((':' 'ident') | (':' 'ident')? ('=' EXPR)) ('\n' | ';')
bool parse_variable(Pack * pack, Node * node) {
    auto lettok = parse_token(pack, TokenId::LET, TokenId::NEWLINE);
    CHECK_RET_FALSE(lettok)

    auto mut_tok = parse_token(pack, TokenId::MUT, TokenId::NEWLINE);
    
    auto ident = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
    CHECK_RET_FALSE_ERR(ident, pack, "expected identifier")
    
    auto variable = Node(AstId::VARIABLE, ident->value, {{lettok->line, lettok->column}}, build_variable);
    if (mut_tok) variable.nodes.push_back(Node(AstId::MUTABLE, {}, {{mut_tok->line, mut_tok->column}}));

    if (parse_token(pack, TokenId::COLON, TokenId::NEWLINE)) {
        auto _type = parse_token(pack, TokenId::IDENT, TokenId::NEWLINE);
        CHECK_RET_FALSE_ERR(_type, pack, "expected type")

        variable.nodes.push_back(Node(AstId::TYPE, _type->value, {{_type->line, _type->column}}));

        if (parse_token(pack, TokenId::EQUALS, TokenId::NEWLINE)) {
            CHECK_RET_FALSE_ERR(parse_expr(pack, &variable), pack, "expected expression")
        }
    } else {
        CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::EQUALS, TokenId::NEWLINE), pack, "expected '='")
        CHECK_RET_FALSE_ERR(parse_expr(pack, &variable), pack, "expected expression")
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

    auto fnnode = Node(AstId::FUNCTION, ident->value, {{fntok->line, fntok->column}}, build_function);

    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::LPAREN, TokenId::NEWLINE), pack, "expected '('")
    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::RPAREN, TokenId::NEWLINE), pack, "expected ')'")

    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::LBRACE, TokenId::NEWLINE), pack, "expected '{'")

    auto body = Node(AstId::BODY, {}, {});
    while (parse_body(pack, &body));
    fnnode.nodes.push_back(body);

    CHECK_RET_FALSE_ERR(parse_token(pack, TokenId::RBRACE, TokenId::NEWLINE), pack, "expected '}'")

    node->nodes.push_back(fnnode);

    return true;
}
