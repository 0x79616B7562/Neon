#pragma once

#include <neonc.h>


enum class AstId {
    ROOT,

    VARIABLE,
    MUTABLE,
    FUNCTION,
    FUNCTION_END,
    BODY,
    RETURN,
    CALL,

    ARGUMENT,
    VARIADIC,
    TYPE,
    EXPRESSION,
    NUMBER,
    STRING,
    IDENTIFIER,
};

std::ostream & operator<<(std::ostream & os, const AstId id);
