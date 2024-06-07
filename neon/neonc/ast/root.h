#pragma once

#include "node.h"
#include <neonc.h>
#include "function.h"

namespace neonc {
    namespace {
        std::string replace_all(std::string str, const std::string & from, const std::string & to) {
            size_t start_pos = 0;

            while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length();
            }

            return str;
        }
    }

    struct Root : public Node {
        Root(const std::string _file_path): Node(std::nullopt) {
            file_path = replace_all(replace_all(_file_path, "/", "::"), "\\", "::");
        }

        virtual NodeId id() const {
            return NodeId::Root;
        }
        
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

        void finalize(Module & module) {
            for (auto & n : nodes) {
                n->finalize(module);
                
                if (!n->nodes.empty())
                    for (auto & _n : n->nodes)
                        _n->finalize(module);
            }
        }

        std::string file_path;
    };
}
