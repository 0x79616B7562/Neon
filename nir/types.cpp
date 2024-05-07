#include "types.h"

#include <iostream>

namespace nir {
    std::ostream & operator<<(std::ostream & os, const Type type) {
        switch (type) {
            case VOID: return os << "void";
            case I32: return os << "i32";
            default: return os << "INVALID TYPE";
        }

        return os;
    }
}
