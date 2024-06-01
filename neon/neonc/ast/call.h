#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Call : public Node {
        Call(const std::string identifier, const std::optional<Position> position): identifier(identifier), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << identifier << ColorYellow << "(" << ColorReset;

            for (uint32_t i = 0; i < nodes.size(); i++) {
                nodes[i]->dump(indentation);

                if (i < nodes.size() - 1)
                    std::cout << ", ";
            }

            std::cout << ColorYellow << ")" << ColorReset;
        }

        std::string identifier;
    };
}
