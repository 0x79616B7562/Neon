#include "analyzer.h"

void Analyzer::analyze(Ast * ast) {
    main_function_has_no_return(ast);
}

void Analyzer::main_function_has_no_return(Ast * ast) const {
    for (auto node : ast->get_root_ptr()->nodes) {
        if (node.id == AstId::FUNCTION) {
            if (node.data.value() == "main") {
                if (node.has_any(AstId::RETURN)) {
                    throw std::runtime_error("main function must not have return");
                }
            }
        }
    }
}
