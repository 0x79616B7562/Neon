#include "build.h"

inline llvm::Value * build_var(Node * node, Module * module, llvm::Type * _type) {
    auto value = module->get_builder()->CreateAlloca(_type, nullptr, "");

    module->get_builder()->CreateStore(create_constant(_type, node->data.value(), module), value);

    return build_load(module, value, _type);
}

inline llvm::Value * build_call(Node * node, Module * module, llvm::Type * _type) {
    auto _ = _type;

    return build_call(node, module);
}

inline llvm::Value * build_identifier(Node * node, Module * module, llvm::Type * _type) {
    if (module->local_variables.contains(node->data.value())) {
        auto value = module->local_variables[node->data.value()];
        return build_load(module, value, _type);
    } else if (std::get<1>(module->get_function()).contains(node->data.value())) {
        return std::get<1>(module->get_function())[node->data.value()];
    } else {
        throw std::invalid_argument("unknown expr id");
    }
}

inline llvm::Value * build_op(AstId op, Module * module, llvm::Value * _f, llvm::Value * _s, llvm::Type * _type) {
    llvm::Value * value = _f;

    switch (op) {
        case AstId::OPERATOR_PLUS:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateAdd(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFAdd(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_MINUS:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateSub(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFSub(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_SLASH:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateSDiv(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFDiv(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_ASTERISK:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateMul(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFMul(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_PERCENT:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateSRem(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFRem(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_EQUAL:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateICmpEQ(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFCmpOEQ(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_NOT_EQUAL:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateICmpNE(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFCmpONE(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_GREATER_THAN:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateICmpSGT(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFCmpOGT(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_LESS_THAN:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateICmpSLT(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFCmpOLT(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_GREATER_THAN_OR_EQUAL:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateICmpSGE(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFCmpOGE(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_LESS_THAN_OR_EQUAL:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateICmpSLE(_f, _s);
                } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                    value = module->get_builder()->CreateFCmpOLE(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_NOT:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateNot(_f);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_AND:
        case AstId::OPERATOR_B_AND:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateAnd(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_OR:
        case AstId::OPERATOR_B_OR:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateOr(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_B_XOR:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateXor(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_B_LEFT_SHIFT:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateShl(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        case AstId::OPERATOR_B_RIGHT_SHIFT:
            {
                if (_type->isIntegerTy()) {
                    value = module->get_builder()->CreateLShr(_f, _s);
                } else {
                    throw std::invalid_argument("invalid type operation");
                }
            }
            break;
        default:
            throw std::invalid_argument("unknown op");
            exit(0);
    }

    return value;
}

llvm::Value * build_expression(Node * node, Module * module, llvm::Type * _type) {
    llvm::Value * value = nullptr;

    AstId op = AstId::NONE;

    for (auto & node : node->nodes) {
        switch (node.id) {
        case AstId::EXPRESSION:
            {
                auto _value = build_expression(&node, module, _type);
                value = op == AstId::NONE ? _value : build_op(op, module, value, _value, _type);
            }
            break;
        case AstId::STRING:
            {
                value = build_var(&node, module, _type);
            
                if (op != AstId::NONE) {
                    throw std::invalid_argument("operations on str is not supported");
                }
            }
            break;
        case AstId::NUMBER:
        case AstId::FLOATING_NUMBER:
        case AstId::BOOLEAN:
            {
                auto _value = build_var(&node, module, _type);
                value = op == AstId::NONE ? _value : build_op(op, module, value, _value, _type);
            }
            break;
        case AstId::IDENTIFIER:
            {
                auto _value = build_identifier(&node, module, _type);
                value = op == AstId::NONE ? _value : build_op(op, module, value, _value, _type);
            }
            break;
        case AstId::CALL:
            {
                auto _value = build_call(&node, module, _type);
                value = op == AstId::NONE ? _value : build_op(op, module, value, _value, _type);
            }
            break;
        case AstId::OPERATOR_PLUS:
        case AstId::OPERATOR_MINUS:
        case AstId::OPERATOR_SLASH:
        case AstId::OPERATOR_ASTERISK:
        case AstId::OPERATOR_PERCENT:
        case AstId::OPERATOR_EQUAL:
        case AstId::OPERATOR_NOT_EQUAL:
        case AstId::OPERATOR_GREATER_THAN:
        case AstId::OPERATOR_LESS_THAN:
        case AstId::OPERATOR_GREATER_THAN_OR_EQUAL:
        case AstId::OPERATOR_LESS_THAN_OR_EQUAL:
        case AstId::OPERATOR_NOT:
        case AstId::OPERATOR_AND:
        case AstId::OPERATOR_B_AND:
        case AstId::OPERATOR_OR:
        case AstId::OPERATOR_B_OR:
        case AstId::OPERATOR_B_XOR:
        case AstId::OPERATOR_B_LEFT_SHIFT:
        case AstId::OPERATOR_B_RIGHT_SHIFT:
            op = node.id;
            break;
        default:
            std::cout << "unknown node id in build_expression: " << node.id << std::endl;
            exit(0);
        }
    }

    return value;
}
