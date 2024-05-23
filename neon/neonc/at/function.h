#pragma once

#include <neonc.h>
#include "argument.h"

namespace neonc {
    class Function {
    public:
        Function(
            const std::string identifier,
            const bool has_body,
            const std::string type,
            const std::vector<Argument> arguments,

            const std::optional<std::string> variadic
        ): identifier(identifier), has_body(has_body), type(type), arguments(arguments), variadic(variadic) {}

        void dump() const;
    private:
        std::string identifier;
        bool has_body;
        std::string type;

        std::optional<std::string> variadic;

        std::vector<Argument> arguments;
    };
}
