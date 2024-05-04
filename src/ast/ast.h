#pragma once

#include "node.h"

class AST {
private:
    Node root;
public:
    AST() = default;

    Node * get_root();
};
