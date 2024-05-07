#include "ast.h"

Node * Ast::get_root_ptr() {
    return &root;
}

void Ast::dump() const {
    root.dump(0);
}
