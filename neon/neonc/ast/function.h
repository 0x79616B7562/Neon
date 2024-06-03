#pragma once

#include "node.h"
#include <neonc.h>
#include "argument.h"
#include "../llvm/util/str_to_type.h"

namespace neonc {
    struct Function : public Node {
        Function(
            const std::string identifier,
            const std::optional<Position> position
        ): identifier(identifier), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::indent(indentation) << cli::colorize("fn ", indentation) << identifier << "(";

            for (uint32_t i = 0; i < arguments.size(); i++) {
                arguments[i].dump();

                if (i < arguments.size() - 1)
                    std::cout << ", ";
            }

            std::cout << ") ";

            if (return_type)
                std::cout << return_type.value() << " ";

            std::cout << "{\n";

            for (auto & node : nodes)
                node->dump(indentation + 1);

            std::cout << cli::indent(indentation) << "}";

            std::cout << std::endl;
        }

        void * build(Module & module) {
            std::vector<llvm::Type *> args;

            for (auto & arg : arguments) {
                args.push_back(str_to_type(module, arg.get_type().value()));
            }

            auto func_type = llvm::FunctionType::get(
                return_type ? str_to_type(module, return_type.value()) : llvm::Type::getVoidTy(*module.context),
                args,
                is_variadic
            );

            auto func = llvm::Function::Create(
                func_type,
                llvm::Function::ExternalLinkage,
                identifier,
                *module.module
            );

            func->addFnAttr(llvm::Attribute::NoInline);
            func->addFnAttr(llvm::Attribute::OptimizeNone);
            func->addFnAttr(llvm::Attribute::NoUnwind);
            func->addFnAttr("frame-pointer", "all");
            func->addFnAttr("min-legal-vector-width", "0");
            func->addFnAttr("no-trapping-math", "true");
            func->addFnAttr("stack-protector-buffer-size", "8");
            if (!module.target_cpu.empty())
                func->addFnAttr("target-cpu", module.target_cpu);
            if (!module.target_features.empty())
                func->addFnAttr("target-features", module.target_features);
            func->addFnAttr("tune-cpu", "generic");

            //

            if (!is_declaration) {
                llvm::BasicBlock::Create(*module.context, "", func);
                std::shared_ptr<llvm::IRBuilder<>> builder(new llvm::IRBuilder<>(&func->getEntryBlock(), func->getEntryBlock().begin()));
          
                std::map<std::string, llvm::Value *> _arguments;
                for (uint32_t i = 0; i < arguments.size(); i++) {
                    _arguments[arguments[i].get_identifier()] = func->getArg(i);
                }

                module.pointer = identifier;
                module.functions[identifier] = {{func, _arguments}, builder};
            }

            return nullptr;
        }

        void add_argument(Argument argument) {
            arguments.push_back(argument);
        }

        void add_arguments(std::vector<Argument> _args) {
            arguments.insert(arguments.end(), _args.begin(), _args.end());
        }

        void set_return_type(std::optional<std::string> _return_type) {
            return_type = _return_type;
        }

        void set_is_declaration(bool _is_declaration) {
            is_declaration = _is_declaration;
        }

        void set_variadic(bool _is_variadic) {
            is_variadic = _is_variadic;
        }
        
        void set_variadic_type(std::optional<std::string> _variadic_type) {
            variadic_type = _variadic_type;
        }

        const std::string get_variadic_type() const {
            return variadic_type.value();
        }

        bool get_variadic() const {
            return is_variadic;
        }

        const std::string identifier;
    private:
        std::optional<std::string> return_type = std::nullopt;
        std::vector<Argument> arguments;
        bool is_declaration = false;

        bool is_variadic = false;
        std::optional<std::string> variadic_type = std::nullopt;
    };
}
