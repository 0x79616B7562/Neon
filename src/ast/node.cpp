#include "node.h"

void Node::dump(const int indent) const {
    data.dump(indent);

    for (Node child : nodes) {
        child.dump(indent + 1);
    }
}
