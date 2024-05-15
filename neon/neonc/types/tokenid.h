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

    COLON, //:
    EQUALS, //=
    COMMA, //,
    SEMICOLON, //;
    DOT, //.

    ASTERISK, //*
    PLUS, //+
    MINUS, //-
    SLASH, ///
    PERCENT, //%

    EXCLAMATION, //!
    AND, //&
    OR, //|
    GREATER_THAN, //>
    LESS_THAN, //<
    CIRC, //^
    
    LPAREN, //(
    RPAREN, //)

    LBRACE, //{
    RBRACE, //}

    IDENT,
    FLOATING_NUMBER,
    NUMBER,
    STRING,
};

std::ostream & operator<<(std::ostream & os, const TokenId id);
