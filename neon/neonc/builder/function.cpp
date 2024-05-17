#include "build.h"

llvm::Value * build_function(Node * node, Module * module) {
    if (!node->data)
        throw std::invalid_argument("Function node must have inner data");

    auto fnname = node->data.value();

    auto _return_type = node->get_node(AstId::TYPE);

    std::vector<llvm::Type*> args;

    for (auto arg : node->get_all(AstId::ARGUMENT)) {
        auto arg_type = string_to_type(arg->get_node(AstId::TYPE).value()->data.value(), module);
        args.push_back(arg_type);
    }

    auto func_type = llvm::FunctionType::get(
        fnname == "main" ? llvm::Type::getInt32Ty(*module->context) : 
            _return_type.has_value() ? string_to_type(_return_type.value()->data.value(), module) : 
            llvm::Type::getVoidTy(*module->context),
        args,
        node->has_any(AstId::VARIADIC)
    );

    auto function = llvm::Function::Create(
        func_type,
        llvm::Function::ExternalLinkage,
        fnname,
        *module->module
    );

    std::map<std::string, llvm::Value *> function_arguments;
    uint32_t index = 0;
    for (auto arg : node->get_all(AstId::ARGUMENT)) {
        if (!arg->data.has_value())
            throw std::invalid_argument("Argument node must have inner data");

        function_arguments[arg->data.value()] = function->getArg(index);

        index++;
    }

    // TODO: make better fn and param attrs
    function->addFnAttr(llvm::Attribute::NoInline);
    function->addFnAttr(llvm::Attribute::OptimizeNone);
    function->addFnAttr(llvm::Attribute::NoUnwind);
    function->addFnAttr("frame-pointer", "all");
    function->addFnAttr("min-legal-vector-width", "0");
    function->addFnAttr("no-trapping-math", "true");
    function->addFnAttr("stack-protector-buffer-size", "8");
    if (!module->target_cpu.empty())
        function->addFnAttr("target-cpu", module->target_cpu);
    if (!module->target_features.empty())
        function->addFnAttr("target-features", module->target_features);
    function->addFnAttr("tune-cpu", "generic");

    if (!node->contains(AstId::BODY)) {
        function->addParamAttr(0, llvm::Attribute::NoUndef);

        return function;
    }

    llvm::BasicBlock::Create(*module->context, "", function);
    std::shared_ptr<llvm::IRBuilder<>> builder(new llvm::IRBuilder<>(&function->getEntryBlock(), function->getEntryBlock().begin()));

    module->functions[fnname] = {function, function_arguments};
    module->builders[fnname] = std::move(builder);
    module->set_pointer(fnname);

    return std::get<0>(module->functions[fnname]);
}

llvm::Value * build_function_end(Node * node, Module * module) {
    auto _ = node;

    if (std::get<0>(module->get_function())->getName() == "main") {
        module->get_builder()->CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*module->context), 0));
    } else if (std::get<0>(module->get_function())->getReturnType() == llvm::Type::getVoidTy(*module->context)) {
        module->get_builder()->CreateRetVoid();
    }

    std::string str;
    llvm::raw_string_ostream output(str);

    if (llvm::verifyFunction(*std::get<0>(module->get_function()), &output)) {
        module->dump();

        std::cerr << output.str() << std::endl;
        exit(0);
    }

    module->clear();

    return nullptr;
}
