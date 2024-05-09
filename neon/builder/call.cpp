#include "build.h"

void build_call(Node * node, Module * module) {
    auto ident = node->data;

    if (!ident)
        throw std::invalid_argument("call has no ident");

    auto func = module->module->getFunction(ident.value());

    if (func == nullptr) {
        throw std::invalid_argument("function not found: " + ident.value());
    }
    
    module->get_builder()->CreateCall(func);
}
