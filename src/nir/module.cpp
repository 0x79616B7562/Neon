#include "module.h"
#include <string>

namespace nir {
    void Module::dump() const {
        std::cout << ColorCyan << Bold << "Module" << ColorReset << "<" << name << "> {" << std::endl;
        
        for (const auto & f : functions) {
            f.dump();
        }

        std::cout << "}" << std::endl;    
    }

    Function * Module::create_function(const std::string identifier, Type return_type) {
        functions.push_back(Function(identifier, return_type));

        return &functions.back();
    }
}
