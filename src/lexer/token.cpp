#include "token.h"

void Token::dump() const {
    auto v = value;

    if (v.empty()) {
        std::cout << ColorRed << token << ColorReset << std::endl;

        return;
    }

    if (v == "\n") {
        v = "\\n";
    } else if (v == "\t") {
        v = "\\t";
    }

    std::cout << ColorCyan << token << ColorReset << " \"" << v << "\" " << std::to_string(line) << ":" << std::to_string(column) << std::endl;
}
