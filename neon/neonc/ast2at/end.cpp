#include "build.h"

namespace neonc {
    void build_end(Node * node, ActionTree * at) {
        at->pop_insert_stack();
    }
}
