#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Return : public Node {
        Return(const std::optional<Position> position): Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::indent(indentation) << cli::colorize("return ", indentation);

            for (auto & n : nodes)
                n->dump(indentation);

            std::cout << std::endl;
        }
    };
}
