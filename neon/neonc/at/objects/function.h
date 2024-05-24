#pragma once

#include "object.h"
#include "argument.h"

namespace neonc {
    class Function : public Object {
    public:
        Function(
            const std::string identifier,
            const bool has_body,
            const std::string type,
            const std::vector<Argument> arguments,

            const std::optional<std::string> variadic,

            const std::optional<Position> position
        ): identifier(identifier), has_body(has_body), type(type), arguments(arguments), variadic(variadic), Object(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << std::string(indentation * DEF_INDENT_MUL, ' ') << ColorGreen << "fn " << ColorReset << identifier << "(";

            for (uint32_t i = 0; i < arguments.size(); i++) {
                std::cout << arguments[i].identifier << ": " << arguments[i].type;

                if (i < arguments.size() - 1)
                    std::cout << ", ";
            }

            if (variadic.has_value()) {
                if (!arguments.empty())
                    std::cout << ", ";

                std::cout << variadic.value() << ": ";

                std::cout << "...";
            }

            std::cout << ") " << (type == "" ? "void" : type) << (has_body ? " {" : ";");

            if (position)
                std::cout << " // " << position.value().string();

            std::cout << "\n";

            for (auto & obj : objects)
                obj->dump(indentation + 1);

            std::cout << std::string(indentation * DEF_INDENT_MUL, ' ') << (has_body ? "}" : "") << std::endl;
        }
    private:
        std::string identifier;
        bool has_body;
        std::string type;

        std::optional<std::string> variadic;

        std::vector<Argument> arguments;
    };
}
