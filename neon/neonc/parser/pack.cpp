#include "pack.h"
#include <vector>

namespace neonc {
    Token Pack::get() const {
        return tokens[index];
    }

    Token Pack::get_next() const {
        return tokens[index + 1];
    }

    Token Pack::get_previous() const {
        return tokens[index - 1];
    }

    Token Pack::get_offset(const int64_t offset) const {
        return tokens[index + offset];
    }

    bool Pack::is_at_end() const {
        return index >= tokens.size() - 1;
    }

    Token Pack::next() {
        index++;

        return tokens[index];
    }
}
