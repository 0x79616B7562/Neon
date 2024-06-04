#include "ast.h"

namespace neonc {
    std::shared_ptr<Node> AbstractSyntaxTree::get_root_ptr() {
        return root;
    }

    void AbstractSyntaxTree::dump() const {
        root->dump(0);
    }

    void AbstractSyntaxTree::verify() {
        verified = true;
    }

    void AbstractSyntaxTree::build(Module & module) {
        if (!verified) {
            std::cerr << "ICE: unable to build unverified ast, call verify()" << std::endl;
            exit(0);
        }

        root->build(module);
    }
}
