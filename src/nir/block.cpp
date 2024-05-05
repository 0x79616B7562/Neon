#include "block.h"

namespace nir {
    void Block::dump() const {
        std::cout << std::string(4, ' ') << ColorYellow << identifier << ColorReset << ":" << std::endl;
    }
}
