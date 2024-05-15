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
        case TokenId::TRUE: return os << "TRUE";
        case TokenId::FALSE: return os << "FALSE";
        case TokenId::LPAREN: return os << "LPAREN";
        case TokenId::COMMA: return os << "COMMA";
        case TokenId::RPAREN: return os << "RPAREN";
        case TokenId::ASTERISK: return os << "ASTERISK";
        case TokenId::DOT: return os << "DOT";
        case TokenId::PLUS: return os << "PLUS";
        case TokenId::MINUS: return os << "MINUS";
        case TokenId::SLASH: return os << "SLASH";
        case TokenId::PERCENT: return os << "PERCENT";
        case TokenId::EXCLAMATION: return os << "EXCLAMATION";
        case TokenId::AND: return os << "AND";
        case TokenId::OR: return os << "OR";
        case TokenId::GREATER_THAN: return os << "GREATER_THAN";
        case TokenId::LESS_THAN: return os << "LESS_THAN";
        case TokenId::CIRC: return os << "CIRC";
        case TokenId::LBRACE: return os << "LBRACE";
        case TokenId::RBRACE: return os << "RBRACE";
        case TokenId::IDENT: return os << "IDENT";
        case TokenId::FLOATING_NUMBER: return os << "FLOATING_NUM";
        case TokenId::NUMBER: return os << "NUM";
        case TokenId::STRING: return os << "STRING";
        default: return os << "UNKNOWN TOKEN ID: " << id << "\n";
    }

    return os;
}
