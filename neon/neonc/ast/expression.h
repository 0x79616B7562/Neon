#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Expression : public Node {
        Expression(): Node(std::nullopt) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << ColorGreen << BoldFont << "( " << ColorReset;

            for (auto & n : nodes)
                n->dump(indentation);

            std::cout << ColorGreen << BoldFont << " )" << ColorReset;
        }
    };
}
