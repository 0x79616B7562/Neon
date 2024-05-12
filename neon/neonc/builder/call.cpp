#include "build.h"

llvm::Value * build_call(Node * node, Module * module) {
    auto ident = node->data;

    if (!ident)
        throw std::invalid_argument("call has no ident");

    auto func = module->module->getFunction(ident.value());

    std::vector<llvm::Value *> args;
    std::vector<std::vector<llvm::Attribute::AttrKind>> attributes;

    uint c = 0;
    for (auto arg : node->get_all(AstId::ARGUMENT)) {
        auto expr = arg.get_node(AstId::EXPRESSION);

        if (expr) {
            auto value = build_expression(expr.value(), module, func->getArg(c)->getType());

            auto load = build_load(module, value, func->getArg(c)->getType());

            args.push_back(load);

            std::vector<llvm::Attribute::AttrKind> attrs;

            // TODO: resolve attributes

            attributes.push_back(attrs);
        }

        c++;
    }

    if (func == nullptr) {
        throw std::invalid_argument("function not found: " + ident.value());
    }
    
    auto call = module->get_builder()->CreateCall(func, args);

    for (long unsigned int i = 0; i < attributes.size(); i++) {
        for (auto attr : attributes[i]) {
            call->addParamAttr(i, attr);
        }
    }

    return call;
}
