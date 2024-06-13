#pragma once

#include <neonc.h>
#include "../variable.h"

namespace neonc {
    class Scope {
    public:
        Scope() = default;

        void pop();
        void push();

        void add_to_scope(std::shared_ptr<Variable> var);

        std::optional<std::shared_ptr<Variable>> find_variable(const std::string & identifier);
    private:
        std::vector<std::vector<std::shared_ptr<Variable>>> variables;
    };
}
