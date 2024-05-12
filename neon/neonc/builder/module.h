#pragma once

#include <neonc.h>
#include "pass.h"

struct Module {
    Module(std::shared_ptr<llvm::LLVMContext> context, std::shared_ptr<llvm::Module> module): context(context), module(module) {}

    void dump() const;
    void clear();

    llvm::Function * get_function();
    std::shared_ptr<llvm::IRBuilder<>> get_builder();

    std::shared_ptr<llvm::LLVMContext> context;
    std::shared_ptr<llvm::Module> module;

    std::string pointer = ""; // NOTE: update pointer when iterating over ast non-recursively!

    std::map<std::string, llvm::Function *> functions;
    std::map<std::string, std::shared_ptr<llvm::IRBuilder<>>> builders;

    std::map<std::string, llvm::Value *> local_variables;
};
