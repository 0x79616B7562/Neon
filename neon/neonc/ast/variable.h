#pragma once

#include "node.h"
#include <neonc.h>
#include "../llvm/util/str_to_type.h"
#include "expression.h"

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

        void * build(Module & module) {
            auto _type = str_to_type(module, type.value());

            auto alloca = module.get_builder()->CreateAlloca(_type);

            module.local_variables[identifier] = alloca;

            if (!nodes.empty()) {
                auto expr = std::dynamic_pointer_cast<Expression>(nodes.back());
    
                if (expr) {
                    module.get_builder()->CreateStore(expr->build(module, _type), alloca);
                }
            }

            return nullptr;
        }

        const std::string identifier;
        std::optional<std::string> type;
    };
}
