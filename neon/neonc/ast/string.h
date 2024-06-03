#pragma once

#include "node.h"
#include <neonc.h>

namespace neonc {
    struct String : public Node {
        String(const std::string string, const std::optional<Position> position): string(string), Node(position) {}

        virtual void dump(const uint32_t indentation) const {
            std::cout << "\"" << string << "\"";
        }

        void * build(Module & module) {
            return module.get_builder()->CreateGlobalString(string);
        }

        std::string string;
    };
}
