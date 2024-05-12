#include "build.h"

llvm::Value * build_function(Node * node, Module * module) {
    if (!node->data)
        throw std::invalid_argument("Function node must have inner data");

    auto fnname = node->data.value();

    auto _return_type = node->get_node(AstId::TYPE);

    std::vector<llvm::Type*> args;

    for (auto arg : node->get_all(AstId::ARGUMENT)) {
        auto arg_type = string_to_type(arg.get_node(AstId::TYPE).value()->data.value(), module);
        args.push_back(arg_type);
    }

    auto func_type = llvm::FunctionType::get(
        fnname == "main" ? llvm::Type::getInt32Ty(*module->context) : 
            _return_type.has_value() ? string_to_type(_return_type.value()->data.value(), module) : 
            llvm::Type::getVoidTy(*module->context),
        args,
        node->contains(AstId::VARIADIC)
    );

    auto function = llvm::Function::Create(
        func_type,
        llvm::Function::ExternalLinkage,
        fnname,
        *module->module
    );

    // TODO: make better fn and param attrs
    function->addFnAttr(llvm::Attribute::MustProgress);
    function->addFnAttr(llvm::Attribute::NoInline);
    function->addFnAttr(llvm::Attribute::OptimizeNone);
    function->addFnAttr(llvm::Attribute::NoUnwind);

    if (!node->contains(AstId::BODY)) {
        return function;
    }

    llvm::BasicBlock::Create(*module->context, "", function);
    std::shared_ptr<llvm::IRBuilder<>> builder(new llvm::IRBuilder<>(&function->getEntryBlock(), function->getEntryBlock().begin()));

    module->functions[fnname] = function;
    module->builders[fnname] = std::move(builder);
    module->pointer = fnname;

    return module->functions[fnname];
}

llvm::Value * build_function_end(Node * node, Module * module) {
    if (module->get_function()->getName() == "main") {
        module->get_builder()->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*module->context), 0));
    } else if (module->get_function()->getReturnType() == llvm::Type::getVoidTy(*module->context)) {
        module->get_builder()->CreateRetVoid();
    }

    std::string str;
    llvm::raw_string_ostream output(str);

    if (llvm::verifyFunction(*module->get_function(), &output)) {
        module->dump();

        std::cerr << output.str() << std::endl;
        exit(0);
    }

    module->clear();

    return nullptr;
}
