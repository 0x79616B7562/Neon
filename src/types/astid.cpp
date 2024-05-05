#include "astid.h"

std::ostream & operator<<(std::ostream & os, const AstId id) {
    switch (id) {
        case ROOT: return os << "Root";
        case FUNCTION: return os << "Function";
        default: return os << "UNKNOWN AST ID";
    }

    return os;
}
