#include "function.h"

void build_function(Node * node, BuildData * data) {
    if (!node->data) {
        std::cerr << "function doesnt have identifier" << std::endl;
        exit(1);
    }
}
