#pragma once

#include "../types/tokenid.h"
#include <vector>

const struct {
    TokenId token;
    char * match;
    bool do_discard;
    bool is_regex;
} TOKENS[] = {
    {token: TokenId::WHITESPACE, match: " ", do_discard: true, is_regex: false}, 
    {token: TokenId::TAB, match: "\t", do_discard: true, is_regex: false}, 
    {token: TokenId::NEWLINE, match: "\n", do_discard: false, is_regex: false}, 

    {token: TokenId::FN, match: "fn", do_discard: false, is_regex: false},

    {token: TokenId::LPAREN, match: "(", do_discard: false, is_regex: false},
    {token: TokenId::RPAREN, match: ")", do_discard: false, is_regex: false},

    {token: TokenId::LBRACE, match: "{", do_discard: false, is_regex: false},
    {token: TokenId::RBRACE, match: "}", do_discard: false, is_regex: false},

    {token: TokenId::IDENT, match: "^[a-zA-Z_]+[a-zA-Z0-9_]*$", do_discard: false, is_regex: true},
    {token: TokenId::NUM, match: "^[-]?[0-9_]+[.]?[0-9_]*?$", do_discard: false, is_regex: true},
    {token: TokenId::STRING, match: "^\"(?:\\\\.|[^\"\\\\])*\"$", do_discard: false, is_regex: true},

    {token: TokenId::SINGLELINECOMMENT, match: "^\\/\\/[^\\n\\r]+$", do_discard: false, is_regex: true},
};
