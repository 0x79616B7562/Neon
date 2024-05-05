#pragma once

#include <ostream>

enum Type {
    VOID,

    I32,
};

std::ostream & operator<<(std::ostream & os, const Type type);
