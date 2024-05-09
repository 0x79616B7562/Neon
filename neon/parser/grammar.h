#pragma once

#include "err.h"
#include <iostream>
#include <optional>
#include <cstddef>
#include "pack.h"
#include "../ast/node.h"
#include "../builder/build.h"

const std::optional<Token> parse_token(Pack * pack, const TokenId to_find, const std::optional<TokenId> ignore);

bool parse_call(Pack * pack, Node * node);
bool parse_ident(Pack * pack, Node * node);
bool parse_string(Pack * pack, Node * node);
bool parse_return(Pack * pack, Node * node);
bool parse_num(Pack * pack, Node * node);
bool parse_expr(Pack * pack, Node * node);
bool parse_variable(Pack * pack, Node * node);
bool parse_body(Pack * pack, Node * node);
bool parse_function(Pack * pack, Node * node);
