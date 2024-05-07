#include "block.h"
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>
#include <memory>
#include <optional>
#include <utility>

namespace nir {
    void Block::dump() const {
        std::cout << NirColorGreen << std::string(4, ' ') << identifier << NirColorReset << ":" << std::endl;

        for (auto & object : objects)
            object->dump();
    }

    void Block::build_block(BuildData * data) {
        block = llvm::BasicBlock::Create(*data->context, identifier, data->function);
    }

    void Block::build_objects(BuildData * data) {
        llvm::IRBuilder<> builder(block);
        data->builder = &builder;

        for (auto & obj : objects)
            obj->build(data);

        data->builder = nullptr;
    }

    const std::string Block::get_identifier() const {
        return identifier;
    }

    llvm::BasicBlock * Block::get_block() const {
        return block;
    }
}
