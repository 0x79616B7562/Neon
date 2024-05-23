#include "build.h"

namespace neonc {
    void build_ast(Node * node, ActionTree * at) {
        if (node->build.has_value())
            node->build.value()(node, at);

        for (uint32_t i = 0; i < node->nodes.size(); i++)
            build_ast(&node->nodes[i], at);
    }
}
