#pragma once

#include "../../types.h"
#include <cstdint>

namespace nir {
    struct ConstInt {
        ConstInt(Type type, int64_t value): type(type), value(value) {}

        Type type;
        int64_t value;
    };
}
