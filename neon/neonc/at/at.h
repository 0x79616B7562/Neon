#pragma once

#include <neonc.h>
#include "objects/object.h"
#include "objects/root.h"

namespace neonc {
    class ActionTree {
    public:
        ActionTree();

        void dump() const;

        void push_insert_stack(std::shared_ptr<Object> obj);
        void pop_insert_stack();
        std::shared_ptr<Object> get_insert_stack();
    private:
        std::list<std::shared_ptr<Object>> insert_stack;
        std::shared_ptr<Object> root;
    };
}
