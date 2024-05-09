#include "build.h"

void build_function(Node * node, Module * module) {
    if (!node->data)
        throw std::invalid_argument("Function node must have inner data");

    auto fnname = node->data.value();

    auto _return_type = node->get_node(AstId::TYPE);

    std::vector<llvm::Type*> args; 

    auto func_type = llvm::FunctionType::get(
        fnname == "main" ? llvm::Type::getInt32Ty(*module->context) : 
            _return_type.has_value() ? string_to_type(_return_type.value()->data.value(), module) : 
            llvm::Type::getVoidTy(*module->context),
        args,
        false
    );

    auto function = llvm::Function::Create(
        func_type,
        fnname == "main" ? llvm::Function::ExternalLinkage : llvm::Function::PrivateLinkage,
        fnname,
        *module->module
    );

    function->addFnAttr(llvm::Attribute::MustProgress);
    function->addFnAttr(llvm::Attribute::NoInline);
    function->addFnAttr(llvm::Attribute::OptimizeNone);
    function->addFnAttr(llvm::Attribute::NoUnwind);

    llvm::BasicBlock::Create(*module->context, "", function);
    std::shared_ptr<llvm::IRBuilder<>> builder(new llvm::IRBuilder<>(&function->getEntryBlock(), function->getEntryBlock().begin()));

    module->functions[fnname] = function;
    module->builders[fnname] = std::move(builder);
    module->pointer = fnname;
}

void build_function_end(Node * node, Module * module) {
    if (module->get_function()->getName() == "main") {
        module->get_builder()->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*module->context), 0));
    } else if (module->get_function()->getReturnType() == llvm::Type::getVoidTy(*module->context)) {
        module->get_builder()->CreateRetVoid();
    }
}
