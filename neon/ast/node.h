#pragma once

#include "../types/astid.h"
#include <vector>
#include <iostream>
#include "../util/clicolor.h"
#include <optional>
#include <tuple>
#include "../builder/build_data.h"
#include <algorithm>

struct Node {
    Node(
        const AstId id,
        const std::optional<std::string> data,
        const std::optional<std::tuple<int, int>> position,
        const std::optional<void (*)(Node *, BuildData *)> build = std::nullopt
    ): id(id), data(data), position(position), build(build) {}

    void dump(const int indent) const;

    std::optional<Node *> get_node(AstId id);

    Node * get_last_node();

    AstId id;
    const std::optional<std::string> data;
    std::vector<Node> nodes;

    // column --------------------------|
    // line -----------------------\    |
    const std::optional<std::tuple<int, int>> position;

    //
    std::optional<void (*)(Node *, BuildData *)> build;
};
