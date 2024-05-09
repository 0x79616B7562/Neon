#include "variable.h"

void build_variable(Node * node, BuildData * data) {
    if (!node->data) {
        std::cerr << "variable doesnt have identifier" << std::endl;
        exit(1);
    }
}
