#pragma once

#include "../types/astid.h"
#include "../util/clicolor.h"
#include "../at/at.h"
#include <neonc.h>

namespace neonc {
    struct Node {
        Node(
            const AstId id,
            const std::optional<std::string> data,
            const std::optional<std::tuple<int, int>> position,
            const std::optional<void (*)(Node *, ActionTree *)> build = std::nullopt
        ): id(id), data(data), position(position), build(build) {}

        void dump(const int indent) const;

        void add_node(AstId id, const std::optional<std::string> data);

        std::optional<Node *> get_node(AstId id);
        bool has_any(AstId id) const;
        bool contains(AstId id) const;
        std::vector<Node *> get_all(AstId id, bool recursive = false);

        Node * get_last_node();

        AstId id;
        std::optional<std::string> data;
        std::vector<Node> nodes;

        // column --------------------|
        // line -----------------\    |
        std::optional<std::tuple<int, int>> position;

        //
        std::optional<void (*)(Node *, ActionTree *)> build;
    };
}
