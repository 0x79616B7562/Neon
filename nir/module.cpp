#include "module.h"
#include <string>

namespace nir {
    void Module::dump() const {
        std::cout << NirColorCyan << NirBold << "Module" << NirColorReset << "<" << name << "> {" << std::endl;
        
        for (const auto & f : functions) {
            f.dump();
        }

        std::cout << "}" << std::endl;    
    }

    Function * Module::create_function(const std::string identifier, Type return_type) {
        functions.push_back(Function(identifier, return_type));

        return &functions.back();
    }

    const std::string Module::get_module_name() const {
        std::filesystem::path path(name);
        std::string file = path.filename().string();

        return file;
    }

    std::vector<Function> & Module::get_functions() {
    	return functions;
    }
}
