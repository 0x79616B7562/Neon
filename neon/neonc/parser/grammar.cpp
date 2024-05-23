#include "grammar.h"

#define CHECK_NEWLINE_OR_SEMICOLON if (!accept(pack, TokenId::NEWLINE, {}).has_value()) { \
    if (!accept(pack, TokenId::SEMICOLON, {})) { throw_parse_error(pack, "expected new line or semicolon"); } }

#define PRECEDENCE_SORT(ops) for (unsigned long int i = 2; i < expr.size(); i += 2) { \
    auto & left = expr[i - 2]; auto & op = expr[i - 1]; auto & right = expr[i]; \
    if (ops) { auto result = Node(AstId::EXPRESSION, {}, {}); \
    result.nodes.push_back(left); result.nodes.push_back(op); result.nodes.push_back(right); \
    expr[i - 2] = result; \
    expr.erase(expr.begin() + i - 1, expr.begin() + i + 1); \
    i -= 2; } }

namespace neonc {
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

    void evaluate_expression(Node * node) {
        std::vector<Node> & expr = node->nodes;

        PRECEDENCE_SORT(op.id == AstId::OPERATOR_PERCENT || op.id == AstId::OPERATOR_SLASH || op.id == AstId::OPERATOR_ASTERISK);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_PLUS || op.id == AstId::OPERATOR_MINUS);
        
        PRECEDENCE_SORT(
            op.id == AstId::OPERATOR_EQUAL
            || op.id == AstId::OPERATOR_NOT_EQUAL
            || op.id == AstId::OPERATOR_GREATER_THAN
            || op.id == AstId::OPERATOR_LESS_THAN
            || op.id == AstId::OPERATOR_GREATER_THAN_OR_EQUAL
            || op.id == AstId::OPERATOR_LESS_THAN_OR_EQUAL
        );

        PRECEDENCE_SORT(op.id == AstId::OPERATOR_NOT);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_B_LEFT_SHIFT || op.id == AstId::OPERATOR_B_RIGHT_SHIFT);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_B_AND);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_B_XOR);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_B_OR);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_AND);
        PRECEDENCE_SORT(op.id == AstId::OPERATOR_OR);
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
        auto num = accept(pack, TokenId::NUMBER, TokenId::NEWLINE);

        if (num) {
            node->nodes.push_back(Node(AstId::NUMBER, num->value, {{num->line, num->column}}));

            return true;
        }

        auto fnum = accept(pack, TokenId::FLOATING_NUMBER, TokenId::NEWLINE);

        if (fnum) {
            node->nodes.push_back(Node(AstId::FLOATING_NUMBER, fnum->value, {{fnum->line, fnum->column}}));

            return true;
        }

        return false;
    }

    bool parse_boolean(Pack * pack, Node * node) {
        auto _true = accept(pack, TokenId::TRUE, TokenId::NEWLINE);
        auto _false = accept(pack, TokenId::FALSE, TokenId::NEWLINE);

        if (_true) {
            node->nodes.push_back(Node(AstId::BOOLEAN, "1", {{_true->line, _true->column}}));

            return true;
        }

        if (_false) {
            node->nodes.push_back(Node(AstId::BOOLEAN, "0", {{_false->line, _false->column}}));

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

            node->nodes.push_back(Node(AstId::STRING, _str, {{str->line, str->column}}));

            return true;
        }

        return false;
    }

    bool parse_operator(Pack * pack, Node * node) {
        // +
        if (accept(pack, TokenId::PLUS, TokenId::NEWLINE)) {
            node->nodes.push_back(Node(AstId::OPERATOR_PLUS, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // -
        if (accept(pack, TokenId::MINUS, TokenId::NEWLINE)) {
            node->nodes.push_back(Node(AstId::OPERATOR_MINUS, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // /
        if (accept(pack, TokenId::SLASH, TokenId::NEWLINE)) {
            node->nodes.push_back(Node(AstId::OPERATOR_SLASH, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // *
        if (accept(pack, TokenId::ASTERISK, TokenId::NEWLINE)) {
            node->nodes.push_back(Node(AstId::OPERATOR_ASTERISK, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // %
        if (accept(pack, TokenId::PERCENT, TokenId::NEWLINE)) {
            node->nodes.push_back(Node(AstId::OPERATOR_PERCENT, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // ==
        if (accept(pack, TokenId::EQUALS, TokenId::NEWLINE)) {
            expect(pack, TokenId::EQUALS, {}, "expected '='");

            node->nodes.push_back(Node(AstId::OPERATOR_EQUAL, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // !
        // !=
        if (accept(pack, TokenId::EXCLAMATION, TokenId::NEWLINE)) {
            if (accept(pack, TokenId::EQUALS, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_NOT_EQUAL, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            node->nodes.push_back(Node(AstId::OPERATOR_NOT, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // >
        // >=
        // >>
        if (accept(pack, TokenId::GREATER_THAN, TokenId::NEWLINE)) {
            if (accept(pack, TokenId::EQUALS, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_GREATER_THAN_OR_EQUAL, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            if (accept(pack, TokenId::GREATER_THAN, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_B_RIGHT_SHIFT, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            node->nodes.push_back(Node(AstId::OPERATOR_GREATER_THAN, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // <
        // <=
        // <<
        if (accept(pack, TokenId::LESS_THAN, TokenId::NEWLINE)) {
            if (accept(pack, TokenId::EQUALS, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_LESS_THAN_OR_EQUAL, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            if (accept(pack, TokenId::LESS_THAN, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_B_LEFT_SHIFT, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            node->nodes.push_back(Node(AstId::OPERATOR_LESS_THAN, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // &
        // &&
        if (accept(pack, TokenId::AND, TokenId::NEWLINE)) {
            if (accept(pack, TokenId::AND, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_AND, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            node->nodes.push_back(Node(AstId::OPERATOR_B_AND, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // |
        // ||
        if (accept(pack, TokenId::OR, TokenId::NEWLINE)) {
            if (accept(pack, TokenId::OR, {})) {
                node->nodes.push_back(Node(AstId::OPERATOR_OR, {}, {{pack->get().line, pack->get().column}}));
                return true;
            }

            node->nodes.push_back(Node(AstId::OPERATOR_B_OR, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }
        // ^
        if (accept(pack, TokenId::CIRC, TokenId::NEWLINE)) {
            node->nodes.push_back(Node(AstId::OPERATOR_B_XOR, {}, {{pack->get().line, pack->get().column}}));
            return true;
        }

        return false;
    }

    bool parse_expr(Pack * pack, Node * node) {
        auto expr = Node(AstId::EXPRESSION, {}, {});

    __parse_expr:
        if (accept(pack, TokenId::LPAREN, TokenId::NEWLINE)) {
            if (!parse_expr(pack, &expr))
                return false;

            expect(pack, TokenId::RPAREN, TokenId::NEWLINE, "expected ')'");

            if (parse_operator(pack, &expr))
                goto __parse_expr;
            else {
                evaluate_expression(&expr);

                node->nodes.push_back(expr);

                return true;
            }
        }

        if (!(
            parse_boolean(pack, &expr)
            || parse_number(pack, &expr)
            || parse_ident_in_expr(pack, &expr)
            || parse_string(pack, &expr)
        )) {
            return false;
        }

        if (parse_operator(pack, &expr))
            goto __parse_expr;

        evaluate_expression(&expr);

        node->nodes.push_back(expr);

        return true;
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

            if (accept(pack, TokenId::DOT, TokenId::NEWLINE)) {
                expect(pack, TokenId::DOT, {}, "expected '...'");
                expect(pack, TokenId::DOT, {}, "expected '...'");

                auto argument = Node(AstId::VARIADIC, ident->value, {{ident->line, ident->column}});

                node->nodes.push_back(argument);

                return true;
            }

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

        node->nodes.push_back(fnnode);

        return true;
    }

    inline bool __parse(Pack * pack, Node * node) {
        if (pack->get().token == TokenId::ENDOFFILE) {
            return false;
        } else if (accept(pack, TokenId::NEWLINE, {})) {
            // ignore
        } else if (pack->get().token == TokenId::RBRACE) {
            return false;
        } else if (accept(pack, TokenId::FN, TokenId::NEWLINE)) {
            if (!parse_function(pack, node)) return false;
        } else if (accept(pack, TokenId::LET, TokenId::NEWLINE)) {
            if (!parse_variable(pack, node)) return false;
        } else if (accept(pack, TokenId::RET, TokenId::NEWLINE)) { 
            if (!parse_return(pack, node)) return false;
        } else if (accept(pack, TokenId::IDENT, TokenId::NEWLINE)) {
            if (!parse_ident(pack, node)) return false;
        } else {
            throw_parse_error(pack, "unexpected");
        }

        return true;
    }

    void parse(Pack * pack, Node * node, bool iterate) {
        if (iterate) {
            while (true)
                if (!__parse(pack, node))
                    break;
        } else
            __parse(pack, node);
    }
}
