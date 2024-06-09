#include "analyzer.h"

namespace neonc {
    void Analyzer::analyze(std::shared_ptr<Node> _root) {
        if (auto root = std::dynamic_pointer_cast<Root>(_root); root) {
            for (auto & node : root->nodes) {
                if (auto func = std::dynamic_pointer_cast<Function>(node); func) {
                    analyze_function(root, func);
                } else {
                    // throw error, invalid at top level
                }
            }
        } else {
            std::cerr << "ICE: root node cannot be dyn casted to root class" << std::endl;
            exit(0);
        }
    }

    //

    void Analyzer::analyze_function(std::shared_ptr<Root> root, std::shared_ptr<Function> func) {
        if (func->identifier == "main") {
            if (func->get_return_type()) {
                throw_error(absolute_file_path, func->position, "main function can't have return type");
            }
        }
    }
}
