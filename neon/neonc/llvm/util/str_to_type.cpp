#include "str_to_type.h"

namespace neonc {
    llvm::Type * str_to_type(Module & module, const std::string type) {
        // boolean type
        if (type == "bool") return llvm::Type::getInt1Ty(*module.context);

        // integer types
        if (type == "i8") return llvm::Type::getInt8Ty(*module.context);
        if (type == "i16") return llvm::Type::getInt16Ty(*module.context);
        if (type == "i32") return llvm::Type::getInt32Ty(*module.context);
        if (type == "i64") return llvm::Type::getInt64Ty(*module.context);

        // floating point types
        if (type == "f32") return llvm::Type::getFloatTy(*module.context);
        if (type == "f64") return llvm::Type::getDoubleTy(*module.context);

        return nullptr;
    }
}
