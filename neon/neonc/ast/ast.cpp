#include "ast.h"

Node * AbstractSyntaxTree::get_root_ptr() {
    return &root;
}

const std::string AbstractSyntaxTree::get_root_data() const {
    return root.data ? root.data.value() : "";
}

void AbstractSyntaxTree::dump() const {
    root.dump(0);
}
