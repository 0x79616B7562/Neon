#include "analyzer.h"

namespace neonc {
    bool Analyzer::analyze(std::shared_ptr<Node> _root) {
        if (auto root = std::dynamic_pointer_cast<Root>(_root); root) {
            for (auto & node : root->nodes) {
                if (auto func = std::dynamic_pointer_cast<Function>(node); func) {
                    analyze_function(root, func);
                } else {
                    throw_error(absolute_file_path, node->position, "unexpected");

                    success = false;
                }
            }
        } else {
            std::cerr << "ICE: root node cannot be dyn casted to root class" << std::endl;

            exit(0);
        }

        return success;
    }

    //

    void Analyzer::analyze_function(std::shared_ptr<Root> root, std::shared_ptr<Function> func) {
        for (auto node : func->nodes) {
            if (auto var = std::dynamic_pointer_cast<Variable>(node); var) {
                analyze_variable(root, var);
            }
        }
    }

    void Analyzer::analyze_variable(std::shared_ptr<Root> root, std::shared_ptr<Variable> var) {
        if (!var->type) {
            auto nums = query(var, NodeId::Number);

            std::cout << "found " << nums.size() << " numbers" << std::endl;
            exit(0);
            // type inference
        }

        // type checking
    }
}
