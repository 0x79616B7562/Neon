#pragma once

#include "node.h"

namespace neonc {
    class AbstractSyntaxTree {
    public:
        AbstractSyntaxTree(Node root): root(root) {}

        const std::string get_root_data() const;
        Node * get_root_ptr();
        void dump() const;
    private:
        Node root;
    };
}
