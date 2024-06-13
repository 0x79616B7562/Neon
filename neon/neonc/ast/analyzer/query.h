#pragma once

#include <neonc.h>
#include "../node.h"

namespace neonc {
    std::optional<std::shared_ptr<Node>> query_first(std::shared_ptr<Node> node, NodeId id);
    std::vector<std::shared_ptr<Node>> query(std::shared_ptr<Node> node, NodeId id);
}
