#include "query.h"

namespace neonc {
    std::optional<std::shared_ptr<Node>> query_first(std::shared_ptr<Node> node, NodeId id) {
        if (node->id() == id)
            return node;

        for (auto n : node->nodes)
            if (auto result = query_first(n, id); result)
                return result;

        return std::nullopt;
    }

    std::vector<std::shared_ptr<Node>> query(std::shared_ptr<Node> node, NodeId id) {
        std::vector<std::shared_ptr<Node>> nodes = {};

        if (node->id() == id)
            nodes.push_back(node);

        for (auto n : node->nodes) {
            auto result = query(n, id);

            if (!result.empty())
                nodes.insert(nodes.end(), result.begin(), result.end());
        }

        return nodes;
    }
}
