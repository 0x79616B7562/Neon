#pragma once

#include <ostream>
#include <sstream>

enum AstId {
    ROOT,

    FUNCTION,
};

std::ostream & operator<<(std::ostream & os, const AstId id);
