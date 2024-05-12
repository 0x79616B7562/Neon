#include "astid.h"

std::ostream & operator<<(std::ostream & os, const AstId id) {
    switch (id) {
        case AstId::ROOT: return os << "Root";
        case AstId::VARIABLE: return os << "Variable";
        case AstId::FUNCTION: return os << "Function";
        case AstId::FUNCTION_END: return os << "Function_End";
        case AstId::NUMBER: return os << "Number";
        case AstId::MUTABLE: return os << "Mutable";
        case AstId::RETURN: return os << "Return";
        case AstId::TYPE: return os << "Type";
        case AstId::STRING: return os << "String";
        case AstId::BODY: return os << "Body";
        case AstId::EXPRESSION: return os << "Expression";
        case AstId::CALL: return os << "Call";
        case AstId::ARGUMENT: return os << "Argument";
        case AstId::VARIADIC: return os << "Variadic";
        case AstId::IDENTIFIER: return os << "Identifier";
        default: return os << "UNKNOWN AST ID: " << id;
    }

    return os;
}
