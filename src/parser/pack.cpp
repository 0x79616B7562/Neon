#include "pack.h"
#include <vector>

Token Pack::get() const {
    return tokens[index];
}

bool Pack::is_at_end() const {
    return index >= tokens.size();
}

void Pack::next() {
    index++;
}
