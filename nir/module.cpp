#include "module.h"

namespace nir {
    void Module::dump() const {
        std::cout << NirColorCyan << NirBold << "Module" << NirColorReset << "<" << name << "> {" << std::endl;
        
        for (int i = 0; i < functions.size(); i++) {
            functions[i].dump();
            
            if (i < functions.size() - 1)
                std::cout << "\n";
        }

        std::cout << "}" << std::endl;    
    }

    Function * Module::create_function(const std::string identifier, const Type return_type, std::optional<Source> src) {
        functions.push_back(Function(identifier, return_type, src));

        if (identifier == "main" && return_type != Type::VOID) {
            std::cerr << "main function must be VOID" << std::endl;
            exit(1);
        }

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

    Function * Module::get_last_function() {
    	return &functions.back();
    }
}
