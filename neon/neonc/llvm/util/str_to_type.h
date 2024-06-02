#pragma once

#include <neonc.h>
#include "../module.h"

namespace neonc {
    llvm::Type * str_to_type(Module & module, const std::string type);
}
