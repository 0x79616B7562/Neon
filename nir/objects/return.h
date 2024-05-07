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
        Return(const std::optional<Source> src): Object(src) {}
        Return(const ConstInt const_int, const std::optional<Source> src): const_int(const_int), Object(src) {}

        virtual void dump(int indent) const {
            if (const_int.has_value()) {
                std::cout << std::string(indent * 4, ' ') << "return " << const_int.value().type << " " << const_int.value().value << std::endl;
                return;
            }

            std::cout << std::string(indent * 4, ' ') << "return void" << std::endl; 
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
        const std::optional<ConstInt> const_int = {};
    };
}
