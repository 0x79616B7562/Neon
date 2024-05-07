#pragma once

#include "object.h"
#include <iostream>

namespace nir {
    class Variable : public Object {
    public:
        Variable(const std::string identifier, const bool mut, const std::optional<std::string> data_type, const std::optional<Source> src):
            data_type(data_type), identifier(identifier), mut(mut), Object(src) {}

        virtual void dump(int indent) const {
            std::cout << std::string(indent * 4, ' ') << "let ";

            if (mut) std::cout << "mut ";

            std::cout << identifier << ": ";
       
            if (data_type) std::cout << data_type.value();
            else std::cout << "auto";

            if (src) std::cout << " ; src: {" << std::get<0>(src->position) << ":" << std::get<1>(src->position) << "}";

            std::cout << std::endl;
        }
 
        inline virtual void build(BuildData * data) const {
            data->builder->CreateAlloca(data->builder->getInt32Ty(), nullptr, ""); //  TODO:
        }
    private:
        const std::optional<std::string> data_type;
        const bool mut;
        const std::string identifier;
    };
}
