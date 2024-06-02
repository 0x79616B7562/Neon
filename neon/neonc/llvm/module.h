#pragma once

#include <neonc.h>

namespace neonc {
    struct Module {
        Module(
            std::shared_ptr<llvm::LLVMContext> context,
            std::shared_ptr<llvm::Module> module,
            const std::string target_cpu,
            const std::string target_features
        ): context(context), module(module), target_cpu(target_cpu), target_features(target_features) {}

        void dump() const;
        void verify() const;

        llvm::Function * get_function();
        std::map<std::string, llvm::Value *> & get_arguments();
        std::shared_ptr<llvm::IRBuilder<>> get_builder();

        std::map<std::string, llvm::Value *> local_variables;

        std::string pointer;
        // args ------------------------------------------------------|
        std::map<std::string, std::tuple<std::tuple<llvm::Function *, std::map<std::string, llvm::Value *>>, std::shared_ptr<llvm::IRBuilder<>>>> functions;

        std::shared_ptr<llvm::LLVMContext> context;
        std::shared_ptr<llvm::Module> module;

        const std::string target_cpu;
        const std::string target_features;
    };
}
