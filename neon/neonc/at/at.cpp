#include "at.h"

namespace neonc {
    void ActionTree::dump() const {
        for (auto & func : functions)
            func.dump();
    }

    Function * ActionTree::add_function(
        const std::string identifier,
        const bool has_body,
        const std::string type,
        const std::vector<Argument> arguments,
        const std::optional<std::string> variadic
    ) {
        functions.push_back(Function(identifier, has_body, type, arguments, variadic));

        return &functions.back();
    }
    
    Function * ActionTree::get_last_function() {
        return &functions.back();
    }
}
