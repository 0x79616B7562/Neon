#include "build.h"

void build_variable(Node * node, Module * module) {
    auto _type = node->get_node(AstId::TYPE);

    if (!_type)
        if (!_type.value()->data)
            throw std::invalid_argument("variable has no type");

    auto __type = string_to_type(_type.value()->data.value(), module);

    auto alloca = module->get_builder()->CreateAlloca(__type, nullptr, "");

    auto expr = node->get_node(AstId::EXPRESSION);

    if (expr) {
        auto value = build_expression(expr.value(), module, __type);
        module->get_builder()->CreateStore(value, alloca);
    } else {
        module->get_builder()->CreateStore(module->get_builder()->getInt32(0), alloca);
    }
}
