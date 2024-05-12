#pragma once

#include "../lexer/token.h"
#include "pack.h"
#include "../ast/ast.h"
#include "../util/cwd.h"
#include "grammar.h"
#include <neonc.h>

class Parser {
public:
    Parser() = default;

    const Ast parse_ast(const std::string file_name, std::vector<Token> tokens) const;
private:
};
