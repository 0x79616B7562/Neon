#pragma once

#include <neonc.h>
#include "err.h"
#include "pack.h"
#include "../ast/node.h"
#include "../ast2at/build.h"

namespace neonc {
    const std::optional<Token> parse_type(Pack * pack);

    void evaluate_expression(Node * node);

    bool parse_arguments(Pack * pack, Node * node);
    bool parse_ident_in_expr(Pack * pack, Node * node);
    bool parse_string(Pack * pack, Node * node);
    bool parse_boolean(Pack * pack, Node * node);
    bool parse_number(Pack * pack, Node * node);
    bool parse_operator(Pack * pack, Node * node);
    bool parse_expr(Pack * pack, Node * node);
    bool parse_ident(Pack * pack, Node * node);
    bool parse_return(Pack * pack, Node * node);
    bool parse_variable(Pack * pack, Node * node);
    bool parse_function_arguments(Pack * pack, Node * node);
    bool parse_function(Pack * pack, Node * node);

    void parse(Pack * pack, Node * node, bool iterate = true);
}
