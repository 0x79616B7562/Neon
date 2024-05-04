#pragma once

#include <iostream>
#include <optional>
#include "pack.h"
#include "../ast/node.h"

std::optional<Token> parse_token(Pack * pack, TokenId to_find, std::optional<TokenId> ignore);

bool parse_function(Pack * pack, Node * node);
