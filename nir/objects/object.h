#pragma once

#include "../build_data.h"

namespace nir {
    class Object {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual void dump() const = 0;

        inline virtual void build(BuildData * data) const = 0;
    };
}
