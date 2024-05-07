#pragma once

#include "llvm/llvm.h"
#include <iostream>
#include <memory>
#include <string>
#include "module.h"

namespace nir {
    class Target {
    public:
        Target();

        void nir_module_to_object_file(Module & module, const std::string output_file, bool dump_llvm_ir = false) const;
    private:
        std::shared_ptr<llvm::LLVMContext> context;
        std::string target_triple;
        const llvm::Target * target;
        std::unique_ptr<llvm::TargetMachine> target_machine;
    };
}
