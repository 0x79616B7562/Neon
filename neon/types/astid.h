#pragma once

#include <ostream>
#include <sstream>

enum AstId {
    ROOT,

    VARIABLE,
    MUTABLE,
    FUNCTION,
    BODY,

    TYPE,
    EXPRESSION,
    NUMBER,
};

std::ostream & operator<<(std::ostream & os, const AstId id);
