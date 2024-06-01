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

        virtual void dump(const uint32_t indentation) const {
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

        op::Operator op;
    };
}
