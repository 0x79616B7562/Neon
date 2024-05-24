#pragma once

#include "object.h"

namespace neonc {
    class Root : public Object {
    public:
        Root(): Object(std::nullopt) {}

        virtual void dump(const uint32_t indentation) const {
            for (auto & obj : objects)
                obj->dump(indentation);
        }
    };
}
