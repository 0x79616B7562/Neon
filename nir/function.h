#pragma once

#include <string>
#include <vector>
#include "types.h"
#include "block.h"
#include "build_data.h"

namespace nir {
    class Function {
    public:
        Function(const std::string identifier, Type return_type) : identifier(identifier), return_type(return_type) {}

        void dump() const;

        void add_block(const std::string identifier);

        void build_function(BuildData * data);

        Block * get(const std::string identifier);
    private:
        inline llvm::Type * resolve_return_type(BuildData * data) const;

        const std::string identifier;
        const Type return_type;
    
        std::vector<Block> blocks;
    };
}
