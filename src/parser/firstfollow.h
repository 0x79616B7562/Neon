#pragma once

#include "../types/tokenid.h"
#include "../ast/node.h"
#include "pack.h"
#include "grammar.h"

struct FirstFollow {
    TokenId first;
    bool (*follow)(Pack*, Node*);
};

const FirstFollow FIRST_FOLLOW[] = {
    {first: TokenId::FN, follow: parse_function},
}; 
