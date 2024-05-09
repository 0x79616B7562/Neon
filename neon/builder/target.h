#pragma once

#include "../llvm/llvm.h"
#include <memory>
#include <string>
#include <iostream>
#include "module.h"

class Target {
public:
    Target();

    Module create_module(const std::string module_name) const;

    void dump_target_triple() const;
private:
    std::shared_ptr<llvm::LLVMContext> context;
    std::string target_triple;
    const llvm::Target * target;
    std::unique_ptr<llvm::TargetMachine> target_machine;
};
