#pragma once

#include "object.h"
#include "expression/operator.h"

namespace neonc {
    class Expression : public Object {
    public:
        Expression(
            const std::shared_ptr<Object> left,
            const Operator op,
            const std::shared_ptr<Object> right,
            const std::optional<Position> position = std::nullopt // position should correspond to operator line and column
        ): left(left), op(op), right(right), Object(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << "()" << std::endl;    
        }
    private:
        std::shared_ptr<Object> left;
        Operator op;
        std::shared_ptr<Object> right;
    };
}
