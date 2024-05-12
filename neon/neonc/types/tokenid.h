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

    COLON,
    EQUALS,
    COMMA,
    SEMICOLON,
    DOT,
    ASTERISK,

    LPAREN,
    RPAREN,

    LBRACE,
    RBRACE,

    IDENT,
    NUM,
    STRING,

    SINGLELINECOMMENT,
};

std::ostream & operator<<(std::ostream & os, const TokenId id);
