#include "build.h"

llvm::Value * build_variable(Node * node, Module * module) {
    auto _type = node->get_node(AstId::TYPE);

    if (!_type)
        if (!_type.value()->data)
            throw std::invalid_argument("variable has no type");

    if (!node->data)
        throw std::invalid_argument("variable has no name");

    auto __type = string_to_type(_type.value()->data.value(), module);

    auto alloca = module->get_builder()->CreateAlloca(__type, nullptr, "");

    auto expr = node->get_node(AstId::EXPRESSION);

    if (expr) {
        auto value = build_expression(expr.value(), module, __type);

        module->get_builder()->CreateStore(value, alloca);
    } else {
        module->get_builder()->CreateStore(create_constant(__type, "", module), alloca);
    }

    if (!node->contains(AstId::MUTABLE))
        module->get_builder()->CreateFreeze(alloca);

    module->local_variables[node->data.value()] = alloca;

    return module->local_variables[node->data.value()];
}
