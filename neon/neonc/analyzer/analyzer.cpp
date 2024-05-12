#include "analyzer.h"

void Analyzer::analyze(Ast * ast) {
    main_function_has_no_return(ast);
    main_function_has_no_return_type(ast);
    main_function_has_no_args(ast);
    no_function_inside_function(ast);
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

void Analyzer::main_function_has_no_return_type(Ast * ast) const {
    for (auto node : ast->get_root_ptr()->nodes) {
        if (node.id == AstId::FUNCTION) {
            if (node.data.value() == "main") {
                if (node.contains(AstId::TYPE)) {
                    throw std::runtime_error("main function must not have return type");
                }
            }
        }
    }
}

void Analyzer::main_function_has_no_args(Ast * ast) const {
    for (auto node : ast->get_root_ptr()->nodes) {
        if (node.id == AstId::FUNCTION) {
            if (node.data.value() == "main") {
                if (node.contains(AstId::ARGUMENT)) {
                    throw std::runtime_error("main function must not have any args");
                }
            }
        }
    }
}

void Analyzer::no_function_inside_function(Ast * ast) const {
    for (auto node : ast->get_root_ptr()->nodes) {
        if (node.id == AstId::FUNCTION) {
            if (node.has_any(AstId::FUNCTION)) {
                throw std::runtime_error("function cant contain function");
            }
        }
    }
}
