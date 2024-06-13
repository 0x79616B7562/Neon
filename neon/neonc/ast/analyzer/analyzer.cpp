#include "analyzer.h"

namespace neonc {
    void Analyzer::throw_error(const std::optional<Position> position, const char * message) {
        _throw_error(absolute_file_path, position, message);

        success = false;
    }

    bool Analyzer::analyze(std::shared_ptr<Node> _root) {
        if (auto root = std::dynamic_pointer_cast<Root>(_root); root) {
            for (auto & node : root->nodes) {
                if (auto func = std::dynamic_pointer_cast<Function>(node); func) {
                    scope.push();

                    analyze_function(root, func);
    
                    scope.pop();
                } else {
                    throw_error(node->position, "unexpected");
                }
            }
        } else {
            std::cerr << "ICE: node cannot be dyn casted to root class" << std::endl;

            exit(0);
        }

        return success;
    }

    //

    void Analyzer::analyze_function(std::shared_ptr<Root> root, std::shared_ptr<Function> func) {
        for (auto node : func->nodes) {
            if (auto var = std::dynamic_pointer_cast<Variable>(node); var) {
                scope.add_to_scope(var);

                analyze_variable_type_inference(root, var);
                analyze_variable_type_checking(root, var);
            }
        }
    }

    void Analyzer::analyze_variable_type_inference(std::shared_ptr<Root> root, std::shared_ptr<Variable> var) {
        if (!var->type) {
            if (auto _call = query_first(var, NodeId::Call); _call) {
                auto funcs = query(root, NodeId::Function);

                for (auto fn : funcs) {
                    if (auto func = std::dynamic_pointer_cast<Function>(fn); func) {
                        if (auto call = std::dynamic_pointer_cast<Call>(_call.value()); call) { 
                            if (func->identifier == call->identifier) {
                                if (auto ret_type = func->get_return_type(); ret_type) {
                                    var->type = ret_type.value();
                                } else {
                                    var->type = Type(std::nullopt, _call->get()->position);
                                }

                                break;
                            }
                        } else {
                            goto _err;
                        }
                    } else {
                    _err:
                        std::cerr << "ICE: cannot cast node to function or call" << std::endl;
                        exit(0);
                    }
                }
            } else if (auto _ident = query_first(var, NodeId::Identifier); _ident) {
                if (auto ident = std::dynamic_pointer_cast<Identifier>(_ident.value()); ident) {
                    if (auto result = scope.find_variable(ident->identifier); result) {
                        var->type = result->get()->type;
                    } else {
                        throw_error(ident->position, "undefined");
                    }
                } else {
                    std::cerr << "ICE: cannot cast node to identifier" << std::endl;
                    exit(0);
                }
            } else if (auto _string = query_first(var, NodeId::String); _string) {
                var->type = Type("str", _string->get()->position);
            } else if (auto _boolean = query_first(var, NodeId::Boolean); _boolean) {
                var->type = Type("bool", _boolean->get()->position);
            } else if (auto _num = query_first(var, NodeId::Number); _num) {
                if (auto num = std::dynamic_pointer_cast<Number>(_num.value()); num) {
                    if (num->is_floating_point) {
                        // TODO: size checking
                        var->type = Type("f32", _num->get()->position);
                    } else {
                        // TODO: size checking
                        var->type = Type("i32", _num->get()->position);
                    }
                } else {
                    std::cerr << "ICE: cannot cast node to number" << std::endl;
                    exit(0);
                }
            } else {
                std::cerr << "ICE: cannot type inference" << std::endl;
                exit(0);
            }
        }
    }

    void Analyzer::analyze_variable_type_checking(std::shared_ptr<Root> root, std::shared_ptr<Variable> var) {
        const auto & type = var->type;

        if (!var->nodes.empty()) {
            if (auto expr = std::dynamic_pointer_cast<Expression>(var->nodes.back()); expr) {
                // TODO: need type checking for local variables to work on this
            } else {
                std::cerr << "ICE: cannot cast node to expression" << std::endl;
                exit(0);
            }
        }
    }
}
