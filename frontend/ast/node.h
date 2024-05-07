#pragma once

#include "data.h"
#include <vector>
#include <optional>

struct Node {
    Node(const AstId id, std::vector<Data> data): id(id), data(data) {}
    void dump(const int indent) const;
    std::optional<std::tuple<Data, std::optional<std::tuple<int, int>>>> get_data_by_id(DataId id) const;

    AstId id;
    std::vector<Data> data;
    std::vector<Node> nodes;
};
