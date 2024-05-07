#pragma once

#include "../types/astid.h"
#include "../util/clicolor.h"
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include "../types/dataid.h"

struct Data {
    Data(DataId id): id(id) {}
    Data(DataId id, std::optional<std::string> data): id(id), data(data) {}
    Data(DataId id, std::optional<std::string> data, std::optional<std::tuple<int, int>> position): id(id), data(data), position(position) {}
    std::optional<std::tuple<int, int>> get_position() const;
    void dump(const int indent) const;

    DataId id;
    std::optional<std::string> data;
    // column --------------------\
    // line -----------------\    |
    std::optional<std::tuple<int, int>> position;
};
