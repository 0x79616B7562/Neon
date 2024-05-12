#pragma once

#include "module.h"
#include <neonc.h>

std::string double_backslash_to_single(std::string input);

llvm::Type * string_to_type(const std::string _type, Module * module);
llvm::Value * create_constant(llvm::Type * _type, std::string value, Module * module);
