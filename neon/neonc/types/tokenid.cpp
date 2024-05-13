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
        case TokenId::EQUAL_TO: return os << "EQUAL_TO";
        case TokenId::NOT_EQUAL_TO: return os << "NOT_EQUAL_TO";
        case TokenId::GREATER_THAN: return os << "GREATER_THAN";
        case TokenId::LESS_THAN: return os << "LESS_THAN";
        case TokenId::GREATER_THAN_OR_EQUAL_TO: return os << "GREATER_THAN_OR_EQUAL_TO";
        case TokenId::LESS_THAN_OR_EQUAL_TO: return os << "LESS_THAN_OR_EQUAL_TO";
        case TokenId::NOT: return os << "LOGICAL_NOT";
        case TokenId::AND: return os << "LOGICAL_AND";
        case TokenId::OR: return os << "LOGICAL_OR";
        case TokenId::BITWISE_NOT: return os << "BITWISE_NOT";
        case TokenId::BITWISE_AND: return os << "BITWISE_AND";
        case TokenId::BITWISE_OR: return os << "BITWISE_OR";
        case TokenId::BITWISE_XOR: return os << "BITWISE_XOR";
        case TokenId::BITWISE_LEFT_SHIFT: return os << "BITWISE_LEFT_SHIFT";
        case TokenId::BITWISE_RIGHT_SHIFT: return os << "BITWISE_RIGHT_SHIFT";
        case TokenId::INCREMENT: return os << "INCREMENT";
        case TokenId::DECREMENT: return os << "DECREMENT";
        case TokenId::LBRACE: return os << "LBRACE";
        case TokenId::RBRACE: return os << "RBRACE";
        case TokenId::IDENT: return os << "IDENT";
        case TokenId::FLOATING_NUMBER: return os << "FLOATING_NUM";
        case TokenId::NUMBER: return os << "NUM";
        case TokenId::STRING: return os << "STRING";
        case TokenId::SINGLELINECOMMENT: return os << "SINGLELINECOMMENT";
        default: return os << "UNKNOWN TOKEN ID: " << id << "\n";
    }

    return os;
}
