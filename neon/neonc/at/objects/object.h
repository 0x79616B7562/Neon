#pragma once

#define DEF_INDENT_MUL 4

#include <neonc.h>
#include "../../types/position.h"
#include "../../util/clicolor.h"

namespace neonc {
    class Object {
    public:
        Object(const std::optional<Position> position): position(position) {}
        virtual ~Object() = default;

        virtual void dump(const uint32_t indentation) const = 0;

        template<typename T, typename ... Args>
        std::shared_ptr<T> add_object(Args ... args) {
            objects.push_back(std::make_shared<T>(args...));
            
            return std::dynamic_pointer_cast<T>(objects.back());
        }
    protected:
        std::optional<Position> position;
        
        std::list<std::shared_ptr<Object>> objects;
    };
}
