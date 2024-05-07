#pragma once

#include <iostream>
#include "object.h"
#include "../block.h"

namespace nir {
    class Goto : public Object {
    public:
        Goto(Block * block): block(block) {}

        virtual void dump() const {
            std::cout << std::string(8, ' ') << "goto: " << block->get_identifier() << std::endl; 
        }
        
        inline virtual void build(BuildData * data) const {
            if (block->get_block() == nullptr)
                throw;

            data->builder->CreateBr(block->get_block());
        }
    private:
        const Block * block = nullptr;
    };
}
