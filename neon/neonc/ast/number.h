#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Number : public Node {
        Number(
            const std::string value,
            const bool is_floating_point,
            const std::optional<Position> position
        ): value(value), is_floating_point(is_floating_point), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << value;
        }

        std::string value;
        bool is_floating_point;
    };
}
