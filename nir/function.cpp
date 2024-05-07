#include "function.h"

namespace nir {
    void Function::dump() const {
        std::cout << NirColorGreen << std::string(4, ' ') << "fn " << NirColorReset << identifier << "() " << return_type << " {" << std::endl;

        for (auto & block : blocks)
            block.dump();

        std::cout << std::string(4, ' ') << "}" << std::endl;    
    }

    void Function::add_block(const std::string identifier) {
        blocks.push_back(Block(identifier));
    }

    inline llvm::Type * Function::resolve_return_type(BuildData * data) const { 
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

        data->function = function;

        for (auto & block : blocks)
            block.build_block(data);

        for (auto & block : blocks)
            block.build_objects(data);

        data->function = nullptr;
    }

    Block * Function::get(const std::string identifier) {
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i].get_identifier() == identifier) {
                return &blocks[i];
            }
        }

        std::cerr << "Block doesnt exist" << std::endl;
        exit(1);
    }
}
