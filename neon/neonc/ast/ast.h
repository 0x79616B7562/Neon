#pragma once

#include "node.h"
#include "root.h"

namespace neonc {
    class AbstractSyntaxTree {
    public:
        AbstractSyntaxTree(
            std::shared_ptr<Node> root,
            const std::string absolute_file_path
        ): root(root), absolute_file_path(absolute_file_path) {}

        std::shared_ptr<Node> get_root_ptr();
        void dump() const;
        void verify();
        void build(Module & module);
        void finalize(Module & module);
    private:
        const std::string absolute_file_path;

        bool verified = false;
        bool built = false;

        std::shared_ptr<Node> root;
    };
}
