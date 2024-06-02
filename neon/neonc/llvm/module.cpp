#include "module.h"

namespace neonc {
    void Module::dump() const {
        module->print(llvm::errs(), nullptr);
    }

    void Module::verify() const {
        for (auto & func : module->getFunctionList()) {
            std::string str;
            llvm::raw_string_ostream output(str);

            if (llvm::verifyFunction(func, &output)) {
                std::cerr << output.str() << std::endl;
                exit(0);
            }
        }

        if (llvm::verifyModule(*module, &llvm::errs())) {
            llvm::errs() << "Error: Module verification failed!\n";

            exit(0);
        }
    }

    llvm::Function * Module::get_function() {
        return std::get<0>(std::get<0>(functions[pointer]));
    }

    std::map<std::string, llvm::Value *> & Module::get_arguments() {
        return std::get<1>(std::get<0>(functions[pointer]));
    }
    
    std::shared_ptr<llvm::IRBuilder<>> Module::get_builder() {
        return std::get<1>(functions[pointer]);
    }
}
