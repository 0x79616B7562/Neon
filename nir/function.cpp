#include "function.h"

#define START_INDENT 2

namespace nir {
    void Function::dump() const {
        if (return_type != Type::VOID || identifier != "main")
            std::cout << NirColorGreen << std::string(4, ' ') << "fn " << NirColorReset << identifier << "() " << return_type << " {";
        else
            std::cout << NirColorGreen << std::string(4, ' ') << "fn " << NirColorReset << identifier << "()" << " {";

        if (src.has_value())
            std::cout << " ; src: {" << std::get<0>(src->position) << ":" << std::get<1>(src->position) << "}";

        std::cout << "\n";

        for (auto & obj : objects)
            obj->dump(START_INDENT);

        std::cout << std::string(4, ' ') << "}" << std::endl;    
    }

    inline llvm::Type * Function::resolve_return_type(BuildData * data) const {
        if (identifier == "main")
            return llvm::Type::getInt32Ty(*data->context);

        switch (return_type) {
        case VOID:
            return llvm::Type::getVoidTy(*data->context);
        case I32:
            return llvm::Type::getInt32Ty(*data->context);
        default:
            std::cerr << "Unsupported return type for function" << std::endl;
            exit(1);
        }
    }

    void Function::build_function(BuildData * data) {
        std::vector<llvm::Type*> args; 

        auto func_type = llvm::FunctionType::get(resolve_return_type(data), args, false);
        
        auto function = llvm::Function::Create(
            func_type,
            llvm::Function::ExternalLinkage,
            identifier,
            *data->module
        );

        function->addFnAttr(llvm::Attribute::MustProgress);
        function->addFnAttr(llvm::Attribute::NoInline);
        function->addFnAttr(llvm::Attribute::OptimizeNone);
        function->addFnAttr(llvm::Attribute::NoUnwind);

        auto bb = llvm::BasicBlock::Create(*data->context, "", function);
        llvm::IRBuilder<> builder(&function->getEntryBlock(), function->getEntryBlock().begin());

        data->function = function;
        data->builder = &builder;

        if (return_type == VOID && identifier != "main")
            add_object<Return>(std::nullopt);
        else if (identifier == "main")
            add_object<Return>(ConstInt(Type::I32, 0), std::nullopt);

        for (auto & obj : objects)
            obj->build(data);

        data->builder = nullptr;
        data->function = nullptr;
    }
}
