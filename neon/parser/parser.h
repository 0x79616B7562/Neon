#pragma once

#include "../lexer/token.h"
#include "firstfollow.h"
#include "pack.h"
#include <vector>
#include <iostream>
#include "../ast/ast.h"
#include "../util/cwd.h"

class Parser {
public:
    Parser();

    const Ast parse(const std::string file_name, std::vector<Token> tokens) const;
private:
    void walk(Pack * pack, Node * node) const;
};
