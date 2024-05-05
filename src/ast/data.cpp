#include "data.h"

void Data::dump(const int indent) const {
    std::cout << ColorGray << std::string(indent * 4, '-') << Bold << ColorCyan << id << ColorReset;

    if (data.has_value()) {
        std::cout << ": " << ColorYellow << data.value() << ColorReset;
    }

    if (position.has_value()) {
        std::cout << " <" << std::get<0>(position.value()) << ":" << std::get<1>(position.value()) << ">";
    }

    std::cout << std::endl;
}
