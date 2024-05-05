#pragma once

#include <iostream>
#include <optional>
#include <cstddef>
#include "pack.h"
#include "../ast/node.h"

const std::optional<Token> parse_token(Pack * pack, const TokenId to_find, const std::optional<TokenId> ignore);

bool parse_body(Pack * pack, Node * node);
bool parse_function(Pack * pack, Node * node);
