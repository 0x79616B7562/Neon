#include "ast.h"

namespace neonc {
    std::shared_ptr<Node> AbstractSyntaxTree::get_root_ptr() {
        return root;
    }

    void AbstractSyntaxTree::dump() const {
        root->dump(0);
    }

    void AbstractSyntaxTree::build(Module & module) {
        root->build(module);
    }
}
