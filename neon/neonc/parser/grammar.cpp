#include "grammar.h"

#define CHECK_NEWLINE_OR_SEMICOLON if (!accept(pack, TokenId::NEWLINE, {}).has_value()) { \
    if (!accept(pack, TokenId::SEMICOLON, {})) { throw_parse_error(pack, "expected new line or semicolon"); } }

const std::optional<Token> accept(Pack * pack, const TokenId to_find, const std::optional<TokenId> ignore) {
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

const std::optional<Token> expect(Pack * pack, const TokenId to_find, const std::optional<TokenId> ignore, const char * message) {
    auto result = accept(pack, to_find, ignore);

    if (!result.has_value()) {
        throw_parse_error(pack, message);

        return {};
    }

    return result;
}

//

const std::optional<Token> parse_type(Pack * pack) {
    auto ptr = accept(pack, TokenId::ASTERISK, TokenId::NEWLINE);
    auto _type = accept(pack, TokenId::IDENT, TokenId::NEWLINE);

    std::string __type = "";

    if (ptr) __type += "*";
    
    if (_type) {
        __type += _type->value;
    } else {
        return {};
    }

    return Token {
        .token = TokenId::IDENT,
        .value = __type,
        .line = _type->line,
        .column = _type->column,
    };
}

bool parse_arguments(Pack * pack, Node * node) {
    while (true) {
        auto argument = Node(AstId::ARGUMENT, {}, {});

        if (!parse_expr(pack, &argument)) break;

        node->nodes.push_back(argument);
        
        if (!accept(pack, TokenId::COMMA, TokenId::NEWLINE)) break;
    }

    return true;
}

bool parse_number(Pack * pack, Node * node) {
    auto num = accept(pack, TokenId::NUM, TokenId::NEWLINE);

    if (num) {
        node->nodes.push_back(Node(AstId::NUMBER, num->value, {{num->line, num->column}}));

        return true;
    }

    return false;
}

bool parse_ident_in_expr(Pack * pack, Node * node) {
    auto ident = accept(pack, TokenId::IDENT, TokenId::NEWLINE);

    if (!ident)
        return false;

    if (accept(pack, TokenId::LPAREN, TokenId::NEWLINE)) {
        auto call = Node(AstId::CALL, ident->value, {{ident->line, ident->column}});

        parse_arguments(pack, &call);

        expect(pack, TokenId::RPAREN, TokenId::NEWLINE, "expected ')'");

        node->nodes.push_back(call);
    } else {
        node->nodes.push_back(Node(AstId::IDENTIFIER, ident->value, {{ident->line, ident->column}}));
    }

    return true;
}

bool parse_string(Pack * pack, Node * node) {
    auto str = accept(pack, TokenId::STRING, TokenId::NEWLINE);

    if (str) {
        std::string _str = str->value;
        _str.erase(0, 1);
        _str.erase(_str.size() - 1, 1);

        node->nodes.push_back(Node(AstId::STRING, _str, {{str->line, str->column}}));

        return true;
    }

    return false;
}

bool parse_expr(Pack * pack, Node * node) {
    auto expr = Node(AstId::EXPRESSION, {}, {});

    if (parse_number(pack, &expr)) {
        node->nodes.push_back(expr);

        return true;
    } else if (parse_ident_in_expr(pack, &expr)) {
        node->nodes.push_back(expr);

        return true;
    } else if (parse_string(pack, &expr)) {
        node->nodes.push_back(expr);

        return true;
    }

    return false;
}

bool parse_return(Pack * pack, Node * node) {
    auto retnode = Node(AstId::RETURN, std::nullopt, {{pack->get_previous().line, pack->get_previous().column}}, build_return);

    parse_expr(pack, &retnode);

    CHECK_NEWLINE_OR_SEMICOLON;

    node->nodes.push_back(retnode);

    return true;
}

bool parse_ident(Pack * pack, Node * node) {
    auto ident = pack->get_previous();

    if (accept(pack, TokenId::LPAREN, TokenId::NEWLINE)) {
        auto call = Node(AstId::CALL, ident.value, {{ident.line, ident.column}}, build_call);

        parse_arguments(pack, &call);

        expect(pack, TokenId::RPAREN, TokenId::NEWLINE, "expected ')'");

        node->nodes.push_back(call);
    } else {
        return false;
    }

    CHECK_NEWLINE_OR_SEMICOLON;

    return true;
}

bool parse_variable(Pack * pack, Node * node) {
    auto muttok = accept(pack, TokenId::MUT, TokenId::NEWLINE);
    auto ident = expect(pack, TokenId::IDENT, TokenId::NEWLINE, "expected identifier");

    auto varnode = Node(AstId::VARIABLE, ident->value, {{pack->get_previous().line, pack->get_previous().column}}, build_variable);

    if (muttok)
        varnode.nodes.push_back(Node(AstId::MUTABLE, {}, {{muttok->line, muttok->column}}));

    if (accept(pack, TokenId::COLON, TokenId::NEWLINE)) {
        auto _type = parse_type(pack);

        if (!_type) {
            throw_parse_error(pack, "expected type");

            return false;
        }


        varnode.nodes.push_back(Node(AstId::TYPE, _type->value, {{_type->line, _type->column}}));

        if (accept(pack, TokenId::EQUALS, TokenId::NEWLINE)) {
            if (!parse_expr(pack, &varnode)) {
                throw_parse_error(pack, "expected expression");

                return false;
            }
        }
    } else {
        expect(pack, TokenId::EQUALS, TokenId::NEWLINE, "expected '='");
        
        if (!parse_expr(pack, &varnode)) {
            throw_parse_error(pack, "expected expression");

            return false;
        }
    }

    
    CHECK_NEWLINE_OR_SEMICOLON;

    node->nodes.push_back(varnode);

    return true;
}

bool parse_function_arguments(Pack * pack, Node * node) {
    while (true) {
        auto ident = accept(pack, TokenId::IDENT, TokenId::NEWLINE);

        if (!ident) break;

        expect(pack, TokenId::COLON, TokenId::NEWLINE, "expected ':'");

        auto _type = parse_type(pack);

        if (!_type) {
            throw_parse_error(pack, "expected type");

            return false;
        }

        auto argument = Node(AstId::ARGUMENT, ident->value, {{ident->line, ident->column}});
        argument.nodes.push_back(Node(AstId::TYPE, _type->value, {{_type->line, _type->column}}));
        
        node->nodes.push_back(argument);

        if (!accept(pack, TokenId::COMMA, TokenId::NEWLINE)) break;
    }

    return false;
}

bool parse_function(Pack * pack, Node * node) {
    auto ident = expect(pack, TokenId::IDENT, TokenId::NEWLINE, "expected identifier");

    auto fnnode = Node(AstId::FUNCTION, ident->value, {{pack->get_previous().line, pack->get_previous().column}}, build_function);

    expect(pack, TokenId::LPAREN, TokenId::NEWLINE, "expected '('");

    parse_function_arguments(pack, &fnnode);

    expect(pack, TokenId::RPAREN, TokenId::NEWLINE, "expected ')'");

    auto ret_type = parse_type(pack);

    if (ret_type)
        fnnode.nodes.push_back(Node(AstId::TYPE, ret_type->value, {{ret_type->line, ret_type->column}}));

    if (accept(pack, TokenId::SEMICOLON, TokenId::NEWLINE)) {
        node->nodes.push_back(fnnode);

        return true;
    }

    expect(pack, TokenId::LBRACE, TokenId::NEWLINE, "expected '{'");

    auto body = Node(AstId::BODY, {}, {});
    parse(pack, &body);
    fnnode.nodes.push_back(body);

    expect(pack, TokenId::RBRACE, TokenId::NEWLINE, "expected '}'");

    fnnode.nodes.push_back(Node(AstId::FUNCTION_END, {}, {}, build_function_end));
    node->nodes.push_back(fnnode);

    return true;
}

void parse(Pack * pack, Node * node) {
    while (true) {
        if (pack->get().token == TokenId::ENDOFFILE) {
            break;
        } else if (accept(pack, TokenId::NEWLINE, {}) || accept(pack, TokenId::SINGLELINECOMMENT, {})) {
            // ignore
        } else if (pack->get().token == TokenId::RBRACE) {
            break;
        } else if (accept(pack, TokenId::FN, TokenId::NEWLINE)) {
            if (!parse_function(pack, node)) break;
        } else if (accept(pack, TokenId::LET, TokenId::NEWLINE)) {
            if (!parse_variable(pack, node)) break;
        } else if (accept(pack, TokenId::RET, TokenId::NEWLINE)) { 
            if (!parse_return(pack, node)) break;
        } else if (accept(pack, TokenId::IDENT, TokenId::NEWLINE)) {
            if (!parse_ident(pack, node)) break;
        } else {
            throw_parse_error(pack, "unexpected");
        }
    }
}
