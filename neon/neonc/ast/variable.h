#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Variable : public Node {
        Variable(
            const std::string identifier,
            const std::optional<std::string> type,
            const std::optional<Position> position
        ): identifier(identifier), type(type), Node(position) {}
       
        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::indent(indentation) << cli::colorize("let ", indentation) << identifier;
            std::cout << ": " << (type.has_value() ? type.value() : ColorRed + std::string("unknown") + ColorReset);

            if (!nodes.empty()) {
                std::cout << " = ";

                for (auto & n : nodes)
                    n->dump(indentation);
            }

            std::cout << std::endl;
        }

        const std::string identifier;
        std::optional<std::string> type;
    };
}
