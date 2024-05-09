#pragma once

#include <memory>
#include "../llvm/llvm.h"
#include <map>
#include <string>

struct Module {
    Module(std::shared_ptr<llvm::LLVMContext> context, std::shared_ptr<llvm::Module> module): context(context), module(module) {}

    void dump() const;

    llvm::Function * get_function();
    std::shared_ptr<llvm::IRBuilder<>> get_builder();

    std::shared_ptr<llvm::LLVMContext> context;
    std::shared_ptr<llvm::Module> module;

    std::string pointer = ""; // NOTE: update pointer when iterating over ast non-recursively!

    std::map<std::string, llvm::Function *> functions;
    std::map<std::string, std::shared_ptr<llvm::IRBuilder<>>> builders;
};
