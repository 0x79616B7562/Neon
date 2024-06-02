#pragma once

#include <neonc.h>
#include "pass.h"
#include "module.h"

namespace neonc {
    class Target {
    public:
        Target();

        Module create_module(const std::string module_name) const;

        void module_to_object_file(Module module, const std::string out) const;
    public:
        std::shared_ptr<Pass> pass;
    private:
        std::string target_features;
        std::string target_cpu;

        std::shared_ptr<llvm::LLVMContext> context;
        std::string target_triple;
        const llvm::Target * target;
        std::unique_ptr<llvm::TargetMachine> target_machine;
    };
}
