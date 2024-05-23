#pragma once

#include "../at/at.h"
#include "../ast/node.h"

namespace neonc {
    void build_ast(Node * node, ActionTree * at);

    void build_function(Node * node, ActionTree * at);
    void build_variable(Node * node, ActionTree * at);
    void build_call(Node * node, ActionTree * at);
    void build_return(Node * node, ActionTree * at);
}
