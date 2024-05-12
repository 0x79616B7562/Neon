#include "tokenid.h"

std::ostream & operator<<(std::ostream & os, const TokenId id) {
    switch (id) {
        case TokenId::ENDOFFILE: return os << "ENDOFFILE";
        case TokenId::INVALID: return os << "INVALID";
        case TokenId::WHITESPACE: return os << "WHITESPACE";
        case TokenId::TAB: return os << "TAB";
        case TokenId::NEWLINE: return os << "NEWLINE";
        case TokenId::LET: return os << "LET";
        case TokenId::MUT: return os << "MUT";
        case TokenId::FN: return os << "FN";
        case TokenId::RET: return os << "RETURN";
        case TokenId::COLON: return os << "COLON";
        case TokenId::EQUALS: return os << "EQUALS";
        case TokenId::SEMICOLON: return os << "SEMICOLON";
        case TokenId::LPAREN: return os << "LPAREN";
        case TokenId::COMMA: return os << "COMMA";
        case TokenId::RPAREN: return os << "RPAREN";
        case TokenId::ASTERISK: return os << "Asterisk";
        case TokenId::DOT: return os << "DOT";
        case TokenId::LBRACE: return os << "LBRACE";
        case TokenId::RBRACE: return os << "RBRACE";
        case TokenId::IDENT: return os << "IDENT";
        case TokenId::NUM: return os << "NUM";
        case TokenId::STRING: return os << "STRING";
        case TokenId::SINGLELINECOMMENT: return os << "SINGLELINECOMMENT";
        default: return os << "UNKNOWN TOKEN ID: " << id;
    }

    return os;
}
