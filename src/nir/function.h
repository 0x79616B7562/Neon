#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "definitions.h"
#include "block.h"
#include "types.h"

namespace nir {
    class Function {
    public:
        Function(const std::string identifier, Type return_type) : identifier(identifier), return_type(return_type) {}

        void dump() const;

        Block * create_block(const std::optional<const std::string> identifier);
    private:
        const std::string identifier;
        const Type return_type;

        std::vector<Block> blocks;
    };
}
