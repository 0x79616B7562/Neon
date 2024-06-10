#pragma once

#include <neonc.h>
#include "../node.h"

namespace neonc {
    std::vector<std::shared_ptr<Node>> query(std::shared_ptr<Node> node, NodeId id);
}
