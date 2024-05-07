#pragma once

#include <tuple>

namespace nir {
    struct Source {
        Source(std::tuple<int, int> position): position(position) {}
        
        // column ------\
        // line ---\    |
        std::tuple<int, int> position;
    };
}
