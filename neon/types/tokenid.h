#pragma once

#include <ostream>
#include <sstream>

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
    SEMICOLON,

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
