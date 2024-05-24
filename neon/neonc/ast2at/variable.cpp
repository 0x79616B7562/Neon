#include "build.h"

#include "../at/objects/variable.h"
#include "../at/objects/function.h"

namespace neonc {
    void build_variable(Node * node, ActionTree * at) {
        auto type = node->get_node(AstId::TYPE);

        at->get_insert_stack()->add_object<Variable>(
            node->data.value(),
            type.has_value() ? type.value()->data : std::nullopt,
            node->has_any(AstId::MUTABLE),
            build_expression(node, at),
            node->position
        );
    }
}
