#pragma once

#include <neonc.h>
#include "../util/clicolor.h"
#include "node.h"

namespace neonc {
    class Type : public Node {
    public:
        Type(std::optional<std::string> data, std::optional<Position> position): data(data), Node(position) {}

        virtual NodeId id() const {
            return NodeId::Type;
        }

        virtual void dump(const uint32_t indentation) const {
            (void)indentation;

            if (data) std::cout << data.value();
            else std::cout << "void";
        }

        void * build(Module & module) {
            // boolean type
            if (data == "bool") return llvm::Type::getInt1Ty(*module.context);

            // integer types
            if (data == "i8") return llvm::Type::getInt8Ty(*module.context);
            if (data == "i16") return llvm::Type::getInt16Ty(*module.context);
            if (data == "i32") return llvm::Type::getInt32Ty(*module.context);
            if (data == "i64") return llvm::Type::getInt64Ty(*module.context);

            // floating point types
            if (data == "f32") return llvm::Type::getFloatTy(*module.context);
            if (data == "f64") return llvm::Type::getDoubleTy(*module.context);

            // str
            if (data == "str") return module.dummy_builder->getPtrTy();

            // void
            if (!data) return llvm::Type::getVoidTy(*module.context);

            std::cerr << "ICE: unable to create type" << std::endl;
            exit(0);
        }

        const std::optional<std::string> & get_data() const {
            return data;
        }
    private:
        std::optional<std::string> data = std::nullopt;
    };
}
