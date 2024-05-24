#pragma once

#include "object.h"
#include "expression.h"

namespace neonc {
    class Variable : public Object {
    public:
        Variable(
            const std::string identifier,
            const std::optional<std::string> type,
            const bool is_mutable,
            const std::optional<Expression> expression,
            const std::optional<Position> position = std::nullopt
        ): identifier(identifier), type(type), is_mutable(is_mutable), expression(expression), Object(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << std::string(indentation * DEF_INDENT_MUL, ' ') << ColorYellow << "let " << (is_mutable ? "mut " : "") << ColorReset << identifier << ": ";
                
            if (type)
                std::cout << *type;
            else
                std::cout << ColorRed << "unknown" << ColorReset;

            if (position)
                std::cout << " // " << position.value().string();

            if (expression) {
                std::cout << " = ";
                expression->dump(0);
            }

            std::cout << std::endl;
        }
    private:
        std::string identifier;
        std::optional<std::string> type;
        bool is_mutable;

        std::optional<Expression> expression;
    };
}
