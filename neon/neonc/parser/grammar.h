#pragma once

#include <neonc.h>
#include "err.h"
#include "pack.h"
#include "../ast/node.h"
#include "../builder/build.h"

const std::optional<Token> parse_type(Pack * pack);

bool parse_arguments(Pack * pack, Node * node);
bool parse_ident_in_expr(Pack * pack, Node * node);
bool parse_string(Pack * pack, Node * node);
bool parse_boolean(Pack * pack, Node * node);
bool parse_number(Pack * pack, Node * node);
bool parse_expr(Pack * pack, Node * node);
bool parse_ident(Pack * pack, Node * node);
bool parse_return(Pack * pack, Node * node);
bool parse_variable(Pack * pack, Node * node);
bool parse_function_arguments(Pack * pack, Node * node);
bool parse_function(Pack * pack, Node * node);

void parse(Pack * pack, Node * node);
