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

// void Analyzer::determine_let_types_in_functions(Ast * ast) const {
//     for (unsigned long int i = 0; i < ast->get_root_ptr()->nodes.size(); i++) {
//         Node * node = &ast->get_root_ptr()->nodes[i];
//    
//         if (node->id == AstId::FUNCTION) {
//             auto lets = node->get_all(AstId::VARIABLE, true);
//
//             for (unsigned long int j = 0; j < lets.size(); j++) {
//                 auto expr = lets[j]->get_node(AstId::EXPRESSION);
//
//                 if (expr) { // TODO: make better version, this is pretty basic detection
//                     if (expr.value()->get_node(AstId::NUMBER)) {
//                         lets[j]->add_node(AstId::TYPE, "i32");
//                     } else if (expr.value()->get_node(AstId::FLOATING_NUMBER)) {
//                         lets[j]->add_node(AstId::TYPE, "f32");
//                     } else if (expr.value()->get_node(AstId::STRING)) {
//                         lets[j]->add_node(AstId::TYPE, "str");
//                     } else if (expr.value()->get_node(AstId::BOOLEAN)) {
//                         lets[j]->add_node(AstId::TYPE, "bool");
//                     }
//                 }
//             }
//         }
//     }
// }
