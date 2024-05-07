#pragma once

#include <ostream>
#include <sstream>

enum AstId {
    ROOT,

    VARIABLE,
    FUNCTION,
};

std::ostream & operator<<(std::ostream & os, const AstId id);
