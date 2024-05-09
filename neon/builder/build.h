#pragma once

#include "../ast/node.h"
#include "module.h"
#include "util.h"

llvm::Value * build_expression(Node * node, Module * module, llvm::Type * _type);

void build_call(Node * node, Module * module);
void build_function(Node * node, Module * module);
void build_function_end(Node * node, Module * module);
void build_variable(Node * node, Module * module);
void build_return(Node * node, Module * module);
