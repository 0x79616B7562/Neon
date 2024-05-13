#include "build.h"

llvm::Value * build_expression(Node * node, Module * module, llvm::Type * _type) {
    llvm::Value * value = nullptr;

    auto num = node->get_node(AstId::NUMBER);
    if (num) {
        value = module->get_builder()->CreateAlloca(_type, nullptr, "");

        module->get_builder()->CreateStore(create_constant(_type, num.value()->data.value(), module), value);
    
        value = build_load(module, value, _type);
    }
    
    auto call = node->get_node(AstId::CALL);
    if (call) {
        value = build_call(call.value(), module);
    }

    auto str = node->get_node(AstId::STRING);
    if (str) {
        value = module->get_builder()->CreateAlloca(_type, nullptr, "");

        module->get_builder()->CreateStore(create_constant(_type, str.value()->data.value(), module), value);
    
        value = build_load(module, value, _type);
    }

    auto id = node->get_node(AstId::IDENTIFIER);
    if (id) {
        if (module->local_variables.contains(id.value()->data.value())) {
            value = module->local_variables[id.value()->data.value()];
            value = build_load(module, value, _type);
        } else if (std::get<1>(module->get_function()).contains(id.value()->data.value())) {
            value = std::get<1>(module->get_function())[id.value()->data.value()];
        } else {
            throw std::invalid_argument("unknown expr id");
        }
    }

    return value;
}
