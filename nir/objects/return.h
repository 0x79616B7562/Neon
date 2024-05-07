#pragma once

#include "object.h"
#include <iostream>
#include <llvm/IR/Constants.h>
#include <optional>
#include <string>
#include "value/const_int.h"

namespace nir {
    class Return : public Object {
    public:
        Return() {}
        Return(ConstInt const_int): const_int(const_int) {}

        virtual void dump() const {
            std::cout << std::string(8, ' ') << "return" << std::endl; 
        }
        
        inline virtual void build(BuildData * data) const {
            if (const_int.has_value()) {
                switch (const_int.value().type) {
                case Type::I32:
                    data->builder->CreateRet(data->builder->getInt32(const_int.value().value));
                    break;
                default:
                    std::cerr << "error: return type not supported for const_int" << std::endl;
                    exit(1);
                }
            } else {
                data->builder->CreateRetVoid();
            }
        }
    private:
        std::optional<ConstInt> const_int = {};
    };
}
