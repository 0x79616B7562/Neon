#pragma once

#include "../ast/node.h"
#include "module.h"
#include "util.h"
#include <neonc.h>

llvm::Value * build_expression(Node * node, Module * module, llvm::Type * _type);
llvm::Value * build_load(Module * module, llvm::Value * value, llvm::Type * into);
llvm::Value * build_call(Node * node, Module * module);
llvm::Value * build_function(Node * node, Module * module);
llvm::Value * build_function_end(Node * node, Module * module);
llvm::Value * build_variable(Node * node, Module * module);
llvm::Value * build_return(Node * node, Module * module);
