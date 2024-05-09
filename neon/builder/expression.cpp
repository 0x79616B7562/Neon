#include "build.h"

llvm::Value * build_expression(Node * node, Module * module, llvm::Type * _type) {
    auto num = node->get_node(AstId::NUMBER);

    if (num) {
        auto value = module->get_builder()->CreateAlloca(_type, nullptr, "");

        module->get_builder()->CreateStore(create_constant(_type, num.value()->data.value(), module), value);

        return value;
    }

    return nullptr;
}
