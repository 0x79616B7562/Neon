#pragma once

#include <neonc.h>

namespace neonc {
    enum class AstId {
        NONE,

        ROOT,

        VARIABLE,
        MUTABLE,

        FUNCTION,
         
        BODY,
        END,
        
        RETURN,
        CALL,

        ARGUMENT,
        VARIADIC,
        TYPE,
        EXPRESSION,
        FLOATING_NUMBER,
        NUMBER,
        BOOLEAN,
        STRING,
        IDENTIFIER,

        OPERATOR_PLUS, // +
        OPERATOR_MINUS, // -
        OPERATOR_SLASH, // /
        OPERATOR_ASTERISK, // *
        OPERATOR_PERCENT, // %
        OPERATOR_EQUAL, // ==
        OPERATOR_NOT_EQUAL, // !=
        OPERATOR_GREATER_THAN, // >
        OPERATOR_LESS_THAN, // <
        OPERATOR_GREATER_THAN_OR_EQUAL, // >=
        OPERATOR_LESS_THAN_OR_EQUAL, // <=
        OPERATOR_NOT, // !
        OPERATOR_AND, // &&
        OPERATOR_B_AND, // &
        OPERATOR_OR, // ||
        OPERATOR_B_OR, // |
        OPERATOR_B_XOR, // ^
        OPERATOR_B_LEFT_SHIFT, // <<
        OPERATOR_B_RIGHT_SHIFT, // >>
    };

    std::ostream & operator<<(std::ostream & os, const AstId id);
}
