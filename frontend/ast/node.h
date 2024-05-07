#pragma once

#include "data.h"
#include <optional>
#include <vector>

struct Node {
    Node(Data data) : data(data) {}
    void dump(const int indent) const;

    Data data;
    std::vector<Node> nodes;
};
