#pragma once

#include "node.h"

class Ast {
public:
    Ast(Node root): root(root) {}

    Node * get_root_ptr();
    void dump() const;
private:
    Node root;
};
