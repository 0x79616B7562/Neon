#include "astid.h"

std::ostream & operator<<(std::ostream & os, const AstId id) {
    switch (id) {
        case ROOT: return os << "Root";
        case VARIABLE: return os << "Variable";
        case FUNCTION: return os << "Function";
        case NUMBER: return os << "Number";
        case MUTABLE: return os << "Mutable";
        case TYPE: return os << "Type";
        case BODY: return os << "Body";
        case EXPRESSION: return os << "Expression";
        default: return os << "UNKNOWN AST ID: " << id;
    }

    return os;
}
