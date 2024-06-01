#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Boolean : public Node {
        Boolean(const bool value, const std::optional<Position> position): value(value), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            if (value) std::cout << "true";
            else std::cout << "false";
        }

        bool value;
    };
}
