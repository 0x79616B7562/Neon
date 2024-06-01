#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Root : public Node {
        Root(const std::string file_path): file_path(file_path), Node(std::nullopt) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::colorize("Root", indentation) << "<" << file_path << "> {" << "\n";
            
            for (auto & n : nodes)
                n->dump(indentation + 1);

            std::cout << "}" << std::endl;
        }

        const std::string file_path;
    };
}
