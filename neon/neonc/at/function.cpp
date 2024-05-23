#include "function.h"

namespace neonc {
    void Function::dump() const {
        std::cout << "fn " << identifier << "(";

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

        std::cout << ") " << type << (has_body ? " {\n" : ";");

        std::cout << (has_body ? "}" : "") << std::endl;
    }
}
