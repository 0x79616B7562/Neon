#include "module.h"

void Module::dump() const {
    module->print(llvm::errs(), nullptr);
}

llvm::Function * Module::get_function() {
    return functions[pointer];
}

std::shared_ptr<llvm::IRBuilder<>> Module::get_builder() {
    return builders[pointer];
}
