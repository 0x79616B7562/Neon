#include "build.h"

llvm::Value * build_load(Module * module, llvm::Value * value, llvm::Type * into) {
    return module->get_builder()->CreateLoad(into, value);
}
