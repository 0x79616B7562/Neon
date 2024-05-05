#pragma once

#include <string>
#include <optional>
#include <iostream>
#include "definitions.h"

namespace nir {
    class Block {
    public:
        Block(const std::string identifier): identifier(identifier) {}

        void dump() const;
    private:
        const std::string identifier;
    };
}
