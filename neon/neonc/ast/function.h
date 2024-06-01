#pragma once

#include "node.h"
#include <neonc.h>
#include "argument.h"

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

        void add_argument(Argument argument) {
            arguments.push_back(argument);
        }

        void add_arguments(std::vector<Argument> _args) {
            arguments.insert(arguments.end(), _args.begin(), _args.end());
        }

        void set_return_type(std::optional<std::string> _return_type) {
            return_type = _return_type;
        }

        const std::string identifier;

    private:
        std::optional<std::string> return_type = std::nullopt;
        std::vector<Argument> arguments;
    };
}
