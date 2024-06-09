#pragma once

#include "type.h"
#include "node.h"
#include <neonc.h>
#include "argument.h"

namespace neonc {
    struct Function : public Node {
        Function(
            const std::string identifier,
            const std::optional<Position> position
        ): identifier(identifier), Node(position) {}

        virtual NodeId id() const {
            return NodeId::Function;
        }

        virtual void dump(const uint32_t indentation) const {
            std::cout << cli::indent(indentation) << cli::colorize("fn ", indentation) << identifier << "(";

            for (uint32_t i = 0; i < arguments.size(); i++) {
                arguments[i].dump(indentation);

                if (i < arguments.size() - 1)
                    std::cout << ", ";
            }

            std::cout << ") ";

            if (return_type) {
                return_type->dump(indentation);
                std::cout << " ";
            }

            if (is_declaration) {
                std::cout << ";" << std::endl;

                return;
            }

            std::cout << "{\n";

            for (auto & node : nodes)
                node->dump(indentation + 1);

            std::cout << cli::indent(indentation) << "}";

            std::cout << std::endl;
        }

        void * build(Module & module) {
            std::vector<llvm::Type *> args;
            bool is_variadic = false;

            for (auto & arg : arguments) {
                if (arg.get_variadic()) {
                    is_variadic = true;

                    break;
                }

                auto _type_ = arg.get_type();
                args.push_back((llvm::Type *)(_type_->build(module)));
            }

            auto func_type = llvm::FunctionType::get(
                identifier == "main" ? (llvm::Type *)Type("i32", std::nullopt).build(module) :
                return_type ? (llvm::Type *)return_type->build(module) : llvm::Type::getVoidTy(*module.context),
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

        void finalize(Module & module) {
            if (identifier == "main") {
                module.get_builder(identifier)->CreateRet(module.get_builder()->getInt32(0));

                return;
            }

            if (!return_type) {
                module.get_builder(identifier)->CreateRetVoid();
            }
        }

        void add_argument(Argument argument) {
            arguments.push_back(argument);
        }

        void add_arguments(std::vector<Argument> _args) {
            arguments.insert(arguments.end(), _args.begin(), _args.end());
        }

        void set_return_type(std::optional<Type> _return_type) {
            return_type = _return_type;
        }

        void set_is_declaration(bool _is_declaration) {
            is_declaration = _is_declaration;
        }

        const std::optional<Type> & get_return_type() const {
            return return_type;
        }

        const std::string identifier;
    private:
        std::optional<Type> return_type = std::nullopt;

        std::vector<Argument> arguments;

        bool is_declaration = false;
    };
}
