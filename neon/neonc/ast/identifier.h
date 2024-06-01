#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Identifier : public Node {
        Identifier(const std::string identifier, const std::optional<Position> position): identifier(identifier), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << identifier;
        }

        std::string identifier;
    };
}
