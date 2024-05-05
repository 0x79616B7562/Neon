#include "function.h"

namespace nir {
    void Function::dump() const {
        std::cout << ColorGreen << std::string(4, ' ') << "fn " << ColorReset << identifier << "() " << return_type << " {" << std::endl;
        
        for (const auto & block : blocks) {
            block.dump();
        }

        std::cout << std::string(4, ' ') << "}" << std::endl;    
    }
    
    Block * Function::create_block(const std::optional<const std::string> identifier) {
        blocks.push_back(Block(identifier.has_value() ? identifier.value() : std::to_string(blocks.size())));

        return &blocks.back();
    }
}
