#include "at.h"

namespace neonc {
    ActionTree::ActionTree() {
        root = std::make_shared<Root>();
        push_insert_stack(root);
    }

    void ActionTree::dump() const {
        root->dump(0);
    }
 
    void ActionTree::push_insert_stack(std::shared_ptr<Object> obj) {
        insert_stack.push_back(obj);
    }

    void ActionTree::pop_insert_stack() {
        insert_stack.pop_back();
    }

    std::shared_ptr<Object> ActionTree::get_insert_stack() {
        return insert_stack.back();
    }
}
