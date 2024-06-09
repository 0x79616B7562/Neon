#pragma once

#include <neonc.h>
#include "../types/position.h"
#include "../util/clicolor.h"
#include "node.h"
#include "type.h"

namespace neonc {
    struct Argument : public Node {
        Argument(
            const std::string identifier,
            const std::optional<Type> type,
            const std::optional<Position> position
        ): identifier(identifier), type(type), Node(position) {}
       
        virtual NodeId id() const {
            return NodeId::Argument;
        }

        virtual void dump(const uint32_t indentation) const {
            (void)indentation;

            std::cout << identifier << ": ";
            if (type) { if (is_variadic) std::cout << "..."; type->dump(indentation); }
            else std::cout << ColorRed << "unknown" << ColorReset;
        }

        const std::optional<Type> & get_type() const {
            return type;
        }

        const std::optional<Position> & get_position() const {
            return position;
        }

        const std::string get_identifier() const {
            return identifier;
        }

        bool get_variadic() const {
            return is_variadic;
        }

        void set_type(const std::optional<Type> _type) {
            type = _type;
        }

        void set_variadic(bool _is_variadic) {
            is_variadic = _is_variadic;
        }
    private:
        std::string identifier;
        std::optional<Type> type = std::nullopt;

        bool is_variadic = false;
    };
}
