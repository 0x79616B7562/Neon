#pragma once

#include <neonc.h>
#include "function.h"

namespace neonc {
    class ActionTree {
    public:
        ActionTree() = default;

        void dump() const;

        Function * add_function(
            const std::string identifier,
            const bool has_body,
            const std::string type,
            const std::vector<Argument> arguments,
            const std::optional<std::string> variadic = std::nullopt
        );

        Function * get_last_function();
    private:
        std::list<Function> functions;
    };
}
