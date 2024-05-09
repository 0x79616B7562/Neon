#pragma once

#include "../llvm/llvm.h"
#include <string>
#include "module.h"

llvm::Type * string_to_type(const std::string _type, Module * module);
llvm::Value * create_constant(llvm::Type * _type, const std::string value, Module * module);
