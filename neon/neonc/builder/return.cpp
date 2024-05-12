#include "build.h"

llvm::Value * build_return(Node * node, Module * module) {
    auto expr = node->get_node(AstId::EXPRESSION);

    if (expr) {
        auto value = build_expression(expr.value(), module, module->get_function()->getReturnType()); 

        auto load = build_load(module, value, module->get_function()->getReturnType());

        return module->get_builder()->CreateRet(load);
    }

    return module->get_builder()->CreateRetVoid();
}
