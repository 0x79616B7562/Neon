#pragma once

#include "llvm/llvm.h"
#include <memory>

namespace nir {
    struct BuildData {
        std::shared_ptr<llvm::LLVMContext> context;
        std::shared_ptr<llvm::Module> module;

        llvm::Function * function = nullptr;
        llvm::IRBuilder<> * builder = nullptr;
    };
}
