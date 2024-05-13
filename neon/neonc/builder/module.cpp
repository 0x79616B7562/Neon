#include "module.h"

void Module::dump() const {
    module->print(llvm::errs(), nullptr);
}

void Module::clear() {
    local_variables.clear();
}

void Module::set_pointer(std::string _pointer) {
    pointer = _pointer;
}

 std::tuple<llvm::Function *, std::map<std::string, llvm::Value *>> Module::get_function() {
    return functions[pointer];
}

std::shared_ptr<llvm::IRBuilder<>> Module::get_builder() {
    return builders[pointer];
}
