#pragma once

namespace neonc {
    enum class Operator {
        PLUS, // +
        MINUS, // -
        SLASH, // /
        ASTERISK, // *
        PERCENT, // %
        EQUAL, // ==
        NOT_EQUAL, // !=
        GREATER_THAN, // >
        LESS_THAN, // <
        GREATER_THAN_OR_EQUAL, // >=
        LESS_THAN_OR_EQUAL, // <=
        NOT, // !
        AND, // &&
        B_AND, // &
        OR, // ||
        B_OR, // |
        B_XOR, // ^
        B_LEFT_SHIFT, // <<
        B_RIGHT_SHIFT, // >>
    };
}
