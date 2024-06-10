#pragma once

#include <neonc.h>
#include "err.h"
#include "query.h"
#include "../node.h"
#include "../root.h"
#include "../function.h"
#include "../variable.h"

namespace neonc {
    class Analyzer {
    public:
        Analyzer(const std::string absolute_file_path): absolute_file_path(absolute_file_path) {}

        bool analyze(std::shared_ptr<Node> root);
    private:
        const std::string absolute_file_path;

        bool success = true;

        void analyze_function(std::shared_ptr<Root> root, std::shared_ptr<Function> func);
        void analyze_variable(std::shared_ptr<Root> root, std::shared_ptr<Variable> var);
    };
}
