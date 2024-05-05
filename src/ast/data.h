#pragma once

#include "../types/astid.h"
#include "../util/clicolor.h"
#include <any>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>

struct Data {
    Data(AstId id) : id(id) {}
    Data(AstId id, std::optional<std::string> data) : id(id), data(data) {}
    Data(AstId id, std::optional<std::string> data, std::optional<std::tuple<int, int>> position) : id(id), data(data), position(position) {}
    void dump(const int indent) const;

    AstId id;
    std::optional<std::string> data;
    // column --------------------\
    // line -----------------\    |
    std::optional<std::tuple<int, int>> position;
};
