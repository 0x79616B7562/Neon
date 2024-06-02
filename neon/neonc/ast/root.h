#pragma once

#include "node.h"
#include <neonc.h>
#include "function.h"

namespace neonc {
    struct Root : public Node {
        Root(const std::string file_path): file_path(file_path), Node(std::nullopt) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::colorize("Root", indentation) << "<" << file_path << "> {" << "\n";
            
            for (auto & n : nodes)
                n->dump(indentation + 1);

            std::cout << "}" << std::endl;
        }

        void * build(Module & module) {
            for (auto & n : nodes) // build top nodes
                n->build(module);

            for (auto & n : nodes) { // build insides
                std::shared_ptr<Function> func = std::dynamic_pointer_cast<Function>(n);    
            
                if (func) {
                    module.pointer = func->identifier;
                    
                    for (auto & _n : n->nodes)
                        _n->build(module);
                }
            }

            return nullptr;
        }

        const std::string file_path;
    };
}
