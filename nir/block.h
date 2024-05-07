#pragma once

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <vector>
#include <memory>
#include "objects/object.h"
#include <iostream>
#include "definitions.h"
#include "build_data.h"

namespace nir {
    class Block {
    public:
        Block(const std::string identifier): identifier(identifier) {}

        void dump() const;

        template<typename T, typename ... Args>
        std::shared_ptr<T> add_object(Args ... args) {
            objects.push_back(std::make_shared<T>(args...));
            
            return std::dynamic_pointer_cast<T>(objects.back());
        }

        void build_block(BuildData * data);
        void build_objects(BuildData * data);

        const std::string get_identifier() const;
        llvm::BasicBlock * get_block() const;
    private:
        std::string identifier;
        std::vector<std::shared_ptr<Object>> objects;
    
        llvm::BasicBlock * block = nullptr;
    };
}
