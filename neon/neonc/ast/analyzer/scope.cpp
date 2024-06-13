#include "scope.h"

namespace neonc {
    void Scope::pop() {
        variables.pop_back();
    }

    void Scope::push() {
        variables.push_back({});
    }

    void Scope::add_to_scope(std::shared_ptr<Variable> var) {
        if (variables.empty()) {
            std::cerr << "ICE: local scope vec is empty" << std::endl;
            exit(0);
        }

        variables.back().push_back(var);
    }

    std::optional<std::shared_ptr<Variable>> Scope::find_variable(const std::string & identifier) {
        for (uint32_t i = variables.size(); i-- > 0;) {
            for (auto var : variables[i]) {
                if (var->identifier == identifier)
                    return var;
            }
        }

        return std::nullopt;
    }
}
