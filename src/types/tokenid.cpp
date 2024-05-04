#include "tokenid.h"

std::ostream & operator<<(std::ostream & os, const TokenId id) {
    switch (id) {
        case ENDOFFILE: return os << "ENDOFFILE";
        case INVALID: return os << "INVALID";
        case WHITESPACE: return os << "WHITESPACE";
        case TAB: return os << "TAB";
        case NEWLINE: return os << "NEWLINE";
        case FN: return os << "FN";
        case LPAREN: return os << "LPAREN";
        case RPAREN: return os << "RPAREN";
        case LBRACE: return os << "LBRACE";
        case RBRACE: return os << "RBRACE";
        case IDENT: return os << "IDENT";
        case NUM: return os << "NUM";
        case STRING: return os << "STRING";
        case SINGLELINECOMMENT: return os << "SINGLELINECOMMENT";
        default: return os << "UNKNOWN TOKEN ID";
    }

    return os;
}
