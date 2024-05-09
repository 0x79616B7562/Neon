#pragma once

#include "../types/astid.h"
#include <vector>
#include <iostream>
#include "../util/clicolor.h"
#include <optional>
#include <tuple>
#include <algorithm>
#include "../builder/module.h"

struct Node {
    Node(
        const AstId id,
        const std::optional<std::string> data,
        const std::optional<std::tuple<int, int>> position,
        const std::optional<void (*)(Node *, Module *)> build = std::nullopt
    ): id(id), data(data), position(position), build(build) {}

    void dump(const int indent) const;

    std::optional<Node *> get_node(AstId id);
    bool has_any(AstId id) const;

    Node * get_last_node();

    AstId id;
    const std::optional<std::string> data;
    std::vector<Node> nodes;

    // column --------------------------|
    // line -----------------------\    |
    const std::optional<std::tuple<int, int>> position;

    //
    std::optional<void (*)(Node *, Module *)> build;
};
