#pragma once

#include "node.h"
#include <neonc.h>
#include "expression.h"

namespace neonc {
    struct Return : public Node {
        Return(const std::optional<Position> position): Node(position) {}

        virtual NodeId id() const {
            return NodeId::Return;
        }
        
        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::indent(indentation) << cli::colorize("return ", indentation);

            for (auto & n : nodes)
                n->dump(indentation);

            std::cout << std::endl;
        }

        void * build(Module & module) {
            if (!nodes.empty()) {
                auto expr = std::dynamic_pointer_cast<Expression>(nodes.back());

                if (expr) {
                    auto value = expr->build(module, module.get_function()->getReturnType());

                    module.get_builder()->CreateRet(value);
                }
            } else {
                module.get_builder()->CreateRetVoid();
            }

            return nullptr;
        }
    };
}
