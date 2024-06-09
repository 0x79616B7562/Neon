#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    namespace op {
        enum class Operator {
            PLUS, // +
            MINUS, // -
            SLASH, // /
            ASTERISK, // *
            PERCENT, // %
            EQUAL, // ==
            NOT_EQUAL, // !=
            GREATER_THAN, // >
            LESS_THAN, // <
            GREATER_THAN_OR_EQUAL, // >=
            LESS_THAN_OR_EQUAL, // <=
            NOT, // !
            AND, // &&
            B_AND, // &
            OR, // ||
            B_OR, // |
            B_XOR, // ^
            B_LEFT_SHIFT, // <<
            B_RIGHT_SHIFT, // >>
        };
    }
    
    struct Operator : public Node {
        Operator(op::Operator op): op(op), Node(std::nullopt) {}

        virtual NodeId id() const {
            return NodeId::Operator;
        }
        
        virtual void dump(const uint32_t indentation) const {
            (void)indentation;

            switch (op) {
            case op::Operator::PLUS: std::cout << " + "; break;
            case op::Operator::MINUS: std::cout << " - "; break;
            case op::Operator::SLASH: std::cout << " / "; break;
            case op::Operator::ASTERISK: std::cout << " * "; break;
            case op::Operator::PERCENT: std::cout << " % "; break;
            case op::Operator::EQUAL: std::cout << " == "; break;
            case op::Operator::NOT_EQUAL: std::cout << " != "; break;
            case op::Operator::GREATER_THAN: std::cout << " > "; break;
            case op::Operator::LESS_THAN: std::cout << " < "; break;
            case op::Operator::GREATER_THAN_OR_EQUAL: std::cout << " >= "; break;
            case op::Operator::LESS_THAN_OR_EQUAL: std::cout << " <= "; break;
            case op::Operator::NOT: std::cout << " ! "; break;
            case op::Operator::AND: std::cout << " && "; break;
            case op::Operator::B_AND: std::cout << " & "; break;
            case op::Operator::OR: std::cout << " || "; break;
            case op::Operator::B_OR: std::cout << " | "; break;
            case op::Operator::B_XOR: std::cout << " ^ "; break;
            case op::Operator::B_LEFT_SHIFT: std::cout << " << "; break;
            case op::Operator::B_RIGHT_SHIFT: std::cout << " >> "; break;
            }
        }

        llvm::Value * build(Module & module, llvm::Value * _f, llvm::Value * _s, llvm::Type * _type) {
            llvm::Value * value = _f;

            
                switch (op) {
                case op::Operator::PLUS:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateAdd(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFAdd(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::MINUS:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateSub(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFSub(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::SLASH:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateSDiv(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFDiv(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::ASTERISK:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateMul(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFMul(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::PERCENT:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateSRem(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFRem(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::EQUAL:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateICmpEQ(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFCmpOEQ(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::NOT_EQUAL:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateICmpNE(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFCmpONE(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::GREATER_THAN:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateICmpSGT(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFCmpOGT(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::LESS_THAN:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateICmpSLT(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFCmpOLT(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::GREATER_THAN_OR_EQUAL:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateICmpSGE(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFCmpOGE(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::LESS_THAN_OR_EQUAL:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateICmpSLE(_f, _s);
                        } else if (_type->isFloatTy() || _type->isDoubleTy()) {
                            value = module.get_builder()->CreateFCmpOLE(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::NOT:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateNot(_f);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::AND:
                case op::Operator::B_AND:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateAnd(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::OR:
                case op::Operator::B_OR:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateOr(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::B_XOR:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateXor(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::B_LEFT_SHIFT:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateShl(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                case op::Operator::B_RIGHT_SHIFT:
                    {
                        if (_type->isIntegerTy()) {
                            value = module.get_builder()->CreateLShr(_f, _s);
                        } else {
                            throw std::invalid_argument("ICE: invalid type operation");
                        }
                    }
                    break;
                default:
                    throw std::invalid_argument("ICE: unknown op");
                    exit(0);
            }

            return value;
        }

        op::Operator op;
    };
}
