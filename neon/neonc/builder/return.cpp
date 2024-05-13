#include "build.h"

llvm::Value * build_return(Node * node, Module * module) {
    auto expr = node->get_node(AstId::EXPRESSION);

    if (expr) {
        auto value = build_expression(expr.value(), module, std::get<0>(module->get_function())->getReturnType()); 

        return module->get_builder()->CreateRet(value);
    }

    return module->get_builder()->CreateRetVoid();
}
