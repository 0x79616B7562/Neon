#pragma once

#include <ostream>
enum DataId {
    IDENTIFIER,
    MUTABLE,
    TYPE,
};

std::ostream & operator<<(std::ostream & os, const DataId id);
