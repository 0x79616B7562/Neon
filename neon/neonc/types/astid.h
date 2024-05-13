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
    TYPE,
    EXPRESSION,
    FLOATING_NUMBER,
    NUMBER,
    BOOLEAN,
    STRING,
    IDENTIFIER,
};

std::ostream & operator<<(std::ostream & os, const AstId id);
