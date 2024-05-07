#include "dataid.h"

std::ostream & operator<<(std::ostream & os, const DataId id) {
    switch (id) {
        case IDENTIFIER: return os << "Identifier";
        case MUTABLE: return os << "Mutable";
        case TYPE: return os << "Type";
        default: return os << "UNKNOWN DATA ID: " << id;
    }

    return os;
}
