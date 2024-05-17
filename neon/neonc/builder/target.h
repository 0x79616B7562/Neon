#pragma once

#include <neonc.h>
#include "module.h"
#include "pass.h"

class Target {
public:
    Target();

    Module create_module(const std::string module_name) const;

    void dump_target_triple() const;
    void module_to_object_file(Module module, const std::string out) const;
    void optimize(Module * module) const;

    std::shared_ptr<Pass> pass;

    std::string get_target_features() const;
    std::string get_target_cpu() const;
private:
    std::string target_features;
    std::string target_cpu;

    std::shared_ptr<llvm::LLVMContext> context;
    std::string target_triple;
    const llvm::Target * target;
    std::unique_ptr<llvm::TargetMachine> target_machine;
};
