#pragma once

#include "../ast/ast.h"

class Analyzer {
public:
    Analyzer() = default;

    void analyze(Ast * ast);
private:
    void main_function_has_no_return(Ast * ast) const;
};
