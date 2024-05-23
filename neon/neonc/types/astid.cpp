#include "astid.h"

namespace neonc {
    std::ostream & operator<<(std::ostream & os, const AstId id) {
        switch (id) {
            case AstId::NONE: return os << "None";
            case AstId::ROOT: return os << "Root";
            case AstId::VARIABLE: return os << "Variable";
            case AstId::FUNCTION: return os << "Function";
            case AstId::FLOATING_NUMBER: return os << "Floating_Number";
            case AstId::NUMBER: return os << "Number";
            case AstId::MUTABLE: return os << "Mutable";
            case AstId::RETURN: return os << "Return";
            case AstId::TYPE: return os << "Type";
            case AstId::STRING: return os << "String";
            case AstId::BOOLEAN: return os << "Boolean";
            case AstId::BODY: return os << "Body";
            case AstId::EXPRESSION: return os << "Expression";
            case AstId::CALL: return os << "Call";
            case AstId::ARGUMENT: return os << "Argument";
            case AstId::VARIADIC: return os << "Variadic";
            case AstId::IDENTIFIER: return os << "Identifier";
            case AstId::OPERATOR_PLUS: return os << "Op_Plus";
            case AstId::OPERATOR_MINUS: return os << "Op_Minus";
            case AstId::OPERATOR_SLASH: return os << "Op_Slash";
            case AstId::OPERATOR_ASTERISK: return os << "Op_Asterisk";
            case AstId::OPERATOR_PERCENT: return os << "Op_Percent";
            case AstId::OPERATOR_EQUAL: return os << "Op_Equal";
            case AstId::OPERATOR_NOT_EQUAL: return os << "Op_Not_Equal";
            case AstId::OPERATOR_GREATER_THAN: return os << "Op_Greater_Than";
            case AstId::OPERATOR_LESS_THAN: return os << "Op_Less_Than";
            case AstId::OPERATOR_GREATER_THAN_OR_EQUAL: return os << "Op_Greater_Than_Or_Equal";
            case AstId::OPERATOR_LESS_THAN_OR_EQUAL: return os << "Op_Less_Than_Or_Equal";
            case AstId::OPERATOR_NOT: return os << "Op_Not";
            case AstId::OPERATOR_AND: return os << "Op_And";
            case AstId::OPERATOR_B_AND: return os << "Op_Bitwise_And";
            case AstId::OPERATOR_OR: return os << "Op_Or";
            case AstId::OPERATOR_B_OR: return os << "Op_Bitwise_Or";
            case AstId::OPERATOR_B_XOR: return os << "Op_Bitwise_Xor";
            case AstId::OPERATOR_B_LEFT_SHIFT: return os << "Op_Bitwise_Left_Shift";
            case AstId::OPERATOR_B_RIGHT_SHIFT: return os << "Op_Bitwise_Right_Shift";
            default: return os << "UNKNOWN AST ID: " << id << "\n";
        }

        return os;
    }
}
