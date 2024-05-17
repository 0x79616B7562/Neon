#pragma once

#include <neonc.h>
#include "pass.h"

struct Module {
    Module(
        std::shared_ptr<llvm::LLVMContext> context,
        std::shared_ptr<llvm::Module> module,
        std::string target_features,
        std::string target_cpu
    ): context(context), module(module), target_features(target_features), target_cpu(target_cpu) {}

    void dump() const;
    void clear();
    void set_pointer(std::string pointer);

    std::tuple<llvm::Function *, std::map<std::string, llvm::Value *>> get_function();
    std::shared_ptr<llvm::IRBuilder<>> get_builder();

    std::shared_ptr<llvm::LLVMContext> context;
    std::shared_ptr<llvm::Module> module;

    std::string target_features;
    std::string target_cpu;

    // argument -------------------------------------------------------------\
    //                                                                       |
    std::map<std::string, std::tuple<llvm::Function *, std::map<std::string, llvm::Value *>>> functions;
    std::map<std::string, std::shared_ptr<llvm::IRBuilder<>>> builders;

    std::map<std::string, llvm::Value *> local_variables;
private:
    std::string pointer = ""; // NOTE: update pointer when iterating over ast non-recursively!
};
