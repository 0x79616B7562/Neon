#pragma once

#include "../build_data.h"
#include "../source.h"
#include <optional>

namespace nir {
    class Object {
    public:
        Object(const std::optional<Source> src): src(src) {}
        virtual ~Object() = default;

        virtual void dump(int indent) const = 0;

        inline virtual void build(BuildData * data) const = 0;

        const std::optional<Source> src;
    };
}
