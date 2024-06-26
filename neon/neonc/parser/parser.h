#pragma once

#include "../lexer/token.h"
#include "pack.h"
#include "../ast/ast.h"
#include "../ast/root.h"
#include "../util/cwd.h"
#include "grammar.h"
#include <neonc.h>

namespace neonc {
    class Parser {
    public:
        Parser() = default;

        const AbstractSyntaxTree parse_ast(const std::string absolute_file_path, std::vector<Token> tokens) const;
    private:
    };
}
