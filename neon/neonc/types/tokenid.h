#pragma once

#include <neonc.h>

namespace neonc {
    enum class TokenId {
        ENDOFFILE,

        INVALID,

        WHITESPACE,
        TAB,
        NEWLINE,

        VAR,
        FN,
        RET,
        PUB,

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
}
