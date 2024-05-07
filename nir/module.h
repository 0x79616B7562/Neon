#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "function.h"
#include "definitions.h"
#include "types.h"
#include <filesystem>

namespace nir {
    class Module {
    public:
        Module(const std::string name): name(name) {}

        void dump() const;

        Function * create_function(const std::string identifier, Type return_type);
        const std::string get_module_name() const;
        std::vector<Function> & get_functions();
    private:
        const std::string name;

        std::vector<Function> functions;
    };
}
