#pragma once

#include "node.h"

class Ast {
public:
    Ast(Node root): root(root) {}

    const std::string get_root_data() const;
    Node * get_root_ptr();
    void dump() const;
private:
    Node root;
};
