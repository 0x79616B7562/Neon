#include "pack.h"
#include <vector>

Token Pack::get() const {
    return tokens[index];
}

Token Pack::get_next() const {
    return tokens[index + 1];
}

bool Pack::is_at_end() const {
    return index >= tokens.size();
}

void Pack::next() {
    index++;
}
