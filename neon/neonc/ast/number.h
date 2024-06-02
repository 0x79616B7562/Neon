#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct Number : public Node {
        Number(
            const std::string value,
            const bool is_floating_point,
            const std::optional<Position> position
        ): value(value), is_floating_point(is_floating_point), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << value;
        }

        llvm::Value * build(Module & module, llvm::Type * type) {
            if (type == llvm::Type::getInt8Ty(*module.context)) return module.get_builder()->getInt8(std::stoll(value));
            if (type == llvm::Type::getInt16Ty(*module.context)) return module.get_builder()->getInt16(std::stoll(value));
            if (type == llvm::Type::getInt32Ty(*module.context)) return module.get_builder()->getInt32(std::stoll(value));
            if (type == llvm::Type::getInt64Ty(*module.context)) return module.get_builder()->getInt64(std::stoll(value));
         
            if (type == llvm::Type::getFloatTy(*module.context)) return llvm::ConstantFP::get(llvm::Type::getFloatTy(*module.context), std::stod(value));
            if (type == llvm::Type::getDoubleTy(*module.context)) return llvm::ConstantFP::get(llvm::Type::getDoubleTy(*module.context), std::stod(value));

            throw std::invalid_argument("unknown create_constat type");
        }

        std::string value;
        bool is_floating_point;
    };
}
