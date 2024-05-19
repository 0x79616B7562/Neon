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
        auto expr = arg->get_node(AstId::EXPRESSION);

        if (expr) {
            if (c > func->arg_size() - 1 && func->isVarArg()) { // variadic
                auto value = build_expression(expr.value(), module, llvm::Type::getInt32Ty(*module->context));

                args.push_back(value);

                continue;
            }

            auto arg = func->getArg(c);

            if (arg == nullptr) {
                throw std::invalid_argument("arg is nullptr");
            }

            auto value = build_expression(
                expr.value(),
                module,
                arg->getType()
            );

            args.push_back(value);

            std::vector<llvm::Attribute::AttrKind> attrs;

            if (arg->hasAttribute(llvm::Attribute::NoUndef))
                attrs.push_back(llvm::Attribute::NoUndef);
            if (arg->hasAttribute(llvm::Attribute::Dereferenceable))
                attrs.push_back(llvm::Attribute::Dereferenceable);

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
