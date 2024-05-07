#include "data.h"

std::optional<std::tuple<int, int>> Data::get_position() const {
    return position;
}

void Data::dump(const int indent) const {
    if (data) {
        std::cout << ColorYellow << id << ColorReset << "<" << "\"" << data.value() << "\"";
    } else {
        std::cout << ColorYellow << id << ColorReset << "<";
    }

    if (position.has_value()) {
        if (data) std::cout << " ";
        std::cout << std::get<0>(position.value()) << ":" << std::get<1>(position.value());
    }

    std::cout << ">";
}
