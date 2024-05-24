#include "position.h"

namespace neonc {
    std::string Position::string() const {
        return std::to_string(line) + ":" + std::to_string(column);
    }
}
