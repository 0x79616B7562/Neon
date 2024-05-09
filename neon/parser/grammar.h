#pragma once

#include "err.h"
#include <iostream>
#include <optional>
#include <cstddef>
#include "pack.h"
#include "../ast/node.h"
#include "../builder/function.h"
#include "../builder/variable.h"

const std::optional<Token> parse_token(Pack * pack, const TokenId to_find, const std::optional<TokenId> ignore);

bool parse_num(Pack * pack, Node * node);
bool parse_expr(Pack * pack, Node * node);
bool parse_variable(Pack * pack, Node * node);
bool parse_body(Pack * pack, Node * node);
bool parse_function(Pack * pack, Node * node);
