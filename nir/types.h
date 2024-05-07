#pragma once

#include "llvm/llvm.h"
#include <ostream>

namespace nir {
    enum Type {
        VOID,

        I32,
    };

    std::ostream & operator<<(std::ostream & os, const Type type);
}
