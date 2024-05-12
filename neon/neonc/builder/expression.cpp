#include "build.h"

llvm::Value * build_expression(Node * node, Module * module, llvm::Type * _type) {
    auto num = node->get_node(AstId::NUMBER);
    if (num) {
        auto value = module->get_builder()->CreateAlloca(_type, nullptr, "");

        module->get_builder()->CreateStore(create_constant(_type, num.value()->data.value(), module), value);

        return value;
    }
    
    auto call = node->get_node(AstId::CALL);
    if (call) {
        auto value = build_call(call.value(), module);

        return value;
    }

    auto str = node->get_node(AstId::STRING);
    if (str) {
        auto value = module->get_builder()->CreateAlloca(_type, nullptr, "");

        module->get_builder()->CreateStore(create_constant(_type, str.value()->data.value(), module), value);

        return value;
    }

    auto id = node->get_node(AstId::IDENTIFIER);
    if (id) {
        return module->local_variables[id.value()->data.value()];
    }

    std::cerr << "UNDETECTED NODE IN EXPRESSION" << std::endl;

    return nullptr;
}
