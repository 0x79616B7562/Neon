#include "ast.h"

Node * Ast::get_root_ptr() {
    return &root;
}

const std::string Ast::get_root_data() const {
    return root.data ? root.data.value() : "";
}

void Ast::dump() const {
    root.dump(0);
}
