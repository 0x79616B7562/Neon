#pragma once

#include "node.h"

namespace neonc {
    class AbstractSyntaxTree {
    public:
        AbstractSyntaxTree(std::shared_ptr<Node> root): root(root) {}

        std::shared_ptr<Node> get_root_ptr();
        void dump() const;
        void verify();
        void build(Module & module);
    private:
        bool verified = false;

        std::shared_ptr<Node> root;
    };
}
