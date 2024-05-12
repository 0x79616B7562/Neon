#pragma once

#include "../ast/ast.h"

class Analyzer {
public:
    Analyzer() = default;

    void analyze(Ast * ast);
private:
    void main_function_has_no_return(Ast * ast) const;
    void main_function_has_no_return_type(Ast * ast) const;
    void main_function_has_no_args(Ast * ast) const;
    void no_function_inside_function(Ast * ast) const;
};
