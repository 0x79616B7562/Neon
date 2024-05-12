#pragma once

#include "../types/tokenid.h"
#include <neonc.h>

const struct {
    TokenId token;
    char * match;
    bool do_discard;
    bool is_regex;
} TOKENS[] = {
    {.token = TokenId::WHITESPACE, .match = (char*)" ", .do_discard = true, .is_regex = false},
    {.token = TokenId::TAB, .match = (char*)"\t", .do_discard = true, .is_regex = false}, 
    {.token = TokenId::NEWLINE, .match = (char*)"\n", .do_discard = false, .is_regex = false}, 

    {.token = TokenId::LET, .match = (char*)"let", .do_discard = false, .is_regex = false},
    {.token = TokenId::MUT, .match = (char*)"mut", .do_discard = false, .is_regex = false},
    {.token = TokenId::FN, .match = (char*)"fn", .do_discard = false, .is_regex = false},
    {.token = TokenId::RET, .match = (char*)"return", .do_discard = false, .is_regex = false},

    {.token = TokenId::COLON, .match = (char*)":", .do_discard = false, .is_regex = false},
    {.token = TokenId::EQUALS, .match = (char*)"=", .do_discard = false, .is_regex = false},
    {.token = TokenId::SEMICOLON, .match = (char*)";", .do_discard = false, .is_regex = false},
    {.token = TokenId::COMMA, .match = (char*)",", .do_discard = false, .is_regex = false},
    {.token = TokenId::DOT, .match = (char*)".", .do_discard = false, .is_regex = false},
    {.token = TokenId::ASTERISK, .match = (char*)"*", .do_discard = false, .is_regex = false},

    {.token = TokenId::LPAREN, .match = (char*)"(", .do_discard = false, .is_regex = false},
    {.token = TokenId::RPAREN, .match = (char*)")", .do_discard = false, .is_regex = false},

    {.token = TokenId::LBRACE, .match = (char*)"{", .do_discard = false, .is_regex = false},
    {.token = TokenId::RBRACE, .match = (char*)"}", .do_discard = false, .is_regex = false},

    {.token = TokenId::IDENT, .match = (char*)"^[a-zA-Z_]+[a-zA-Z0-9_]*$", .do_discard = false, .is_regex = true},
    {.token = TokenId::NUM, .match = (char*)"^[-]?[0-9_]+[.]?[0-9_]*?$", .do_discard = false, .is_regex = true},
    {.token = TokenId::STRING, .match = (char*)"^\"(?:\\\\.|[^\"\\\\])*\"$", .do_discard = false, .is_regex = true},

    {.token = TokenId::SINGLELINECOMMENT, .match = (char*)"^\\/\\/[^\\n\\r]+$", .do_discard = false, .is_regex = true},
};
