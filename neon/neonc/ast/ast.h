#pragma once

#include "node.h"
#include "root.h"

namespace neonc {
    class AbstractSyntaxTree {
    public:
        AbstractSyntaxTree(std::shared_ptr<Node> root): root(root) {}

        std::shared_ptr<Node> get_root_ptr();
        void dump() const;
        void verify(Module & module);
        void build(Module & module);
        void finalize(Module & module);
    private:
        bool verified = false;
        bool built = false;

        std::shared_ptr<Node> root;
    };
}
