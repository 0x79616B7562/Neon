#pragma once

#include <ostream>
#include <sstream>

enum class AstId {
    ROOT,

    VARIABLE,
    MUTABLE,
    FUNCTION,
    FUNCTION_END,
    BODY,
    RETURN,
    CALL,

    TYPE,
    EXPRESSION,
    NUMBER,
    STRING,
};

std::ostream & operator<<(std::ostream & os, const AstId id);
