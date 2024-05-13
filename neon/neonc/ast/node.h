#pragma once

#include "../types/astid.h"
#include "../util/clicolor.h"
#include "../builder/module.h"
#include <neonc.h>

struct Node {
    Node(
        const AstId id,
        const std::optional<std::string> data,
        const std::optional<std::tuple<int, int>> position,
        const std::optional<llvm::Value * (*)(Node *, Module *)> build = std::nullopt
    ): id(id), data(data), position(position), build(build) {}

    void dump(const int indent) const;

    void add_node(AstId id, const std::optional<std::string> data);

    std::optional<Node *> get_node(AstId id);
    bool has_any(AstId id) const;
    bool contains(AstId id) const;
    std::vector<Node *> get_all(AstId id, bool recursive = false);

    Node * get_last_node();

    AstId id;
    const std::optional<std::string> data;
    std::vector<Node> nodes;

    // column --------------------------|
    // line -----------------------\    |
    const std::optional<std::tuple<int, int>> position;

    //
    std::optional<llvm::Value * (*)(Node *, Module *)> build;
};
