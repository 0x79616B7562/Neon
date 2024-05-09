#include "build.h"

void build_return(Node * node, Module * module) {
    auto expr = node->get_node(AstId::EXPRESSION);

    if (expr) {
        auto value = build_expression(expr.value(), module, module->get_function()->getReturnType()); 
        module->get_builder()->CreateRet(value);

        return;
    }

    module->get_builder()->CreateRetVoid();
}
