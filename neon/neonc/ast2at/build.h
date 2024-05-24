#pragma once

#include "../at/at.h"
#include "../ast/node.h"
#include "../at/objects/expression.h"

namespace neonc {
    void build_ast(Node * node, ActionTree * at);

    std::optional<Expression> build_expression(Node * node, ActionTree * at);

    void build_function(Node * node, ActionTree * at);
    void build_end(Node * node, ActionTree * at);
    void build_variable(Node * node, ActionTree * at);
    void build_call(Node * node, ActionTree * at);
    void build_return(Node * node, ActionTree * at);
}
