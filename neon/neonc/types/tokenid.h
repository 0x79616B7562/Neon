#pragma once

#include <neonc.h>

enum class TokenId {
    ENDOFFILE,

    INVALID,

    WHITESPACE,
    TAB,
    NEWLINE,

    LET,
    MUT,
    FN,
    RET,

    TRUE,
    FALSE,

    COLON,
    EQUALS,
    COMMA,
    SEMICOLON,
    DOT,

    ASTERISK,
    PLUS,
    MINUS,
    SLASH,
    PERCENT,
    
    EQUAL_TO,
    NOT_EQUAL_TO,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL_TO,
    LESS_THAN_OR_EQUAL_TO,
    
    NOT,
    AND,
    OR,
    
    BITWISE_NOT,
    BITWISE_AND,
    BITWISE_OR,
    BITWISE_XOR,
    BITWISE_LEFT_SHIFT,
    BITWISE_RIGHT_SHIFT,
    
    INCREMENT,
    DECREMENT,

    LPAREN,
    RPAREN,

    LBRACE,
    RBRACE,

    IDENT,
    FLOATING_NUMBER,
    NUMBER,
    STRING,

    SINGLELINECOMMENT,
};

std::ostream & operator<<(std::ostream & os, const TokenId id);
