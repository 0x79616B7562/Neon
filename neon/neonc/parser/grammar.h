#pragma once

#include <neonc.h>
#include "err.h"
#include "pack.h"
#include "../ast/node.h"
#include "../ast/type.h"
#include "../ast/function.h"
#include "../ast/variable.h"
#include "../ast/expression.h"
#include "../ast/number.h"
#include "../ast/operator.h"
#include "../ast/identifier.h"
#include "../ast/string.h"
#include "../ast/boolean.h"
#include "../ast/call.h"
#include "../ast/return.h"

namespace neonc {
    const std::optional<Type> parse_type(Pack * pack);

    void evaluate_expression(Node * node);

    bool parse_ident(Pack * pack, Node * node);
    bool parse_string(Pack * pack, Node * node);
    bool parse_boolean(Pack * pack, Node * node);
    bool parse_number(Pack * pack, Node * node);
    bool parse_operator(Pack * pack, Node * node);
    bool parse_expression(Pack * pack, Node * node);
    bool parse_standalone_expression(Pack * pack, Node * node);
    bool parse_return(Pack * pack, Node * node);
    bool parse_variable(Pack * pack, Node * node);
    bool parse_function_arguments(Pack * pack, std::shared_ptr<Function> node);
    bool parse_function(Pack * pack, Node * node);

    void parse(Pack * pack, std::shared_ptr<Node> node);
}
