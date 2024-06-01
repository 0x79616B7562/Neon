#pragma once

#include <neonc.h>
#include "../types/position.h"
#include "../util/clicolor.h"

namespace neonc {
    struct Argument {
        Argument(
            const std::string identifier,
            const std::optional<std::string> type,
            const std::optional<Position> position
        ): identifier(identifier), type(type), position(position) {}
        
        void dump() const {
            std::cout << identifier << ": " << (type.has_value() ? type.value() : ColorRed + std::string("unknown") + ColorReset);
        }

        const std::optional<std::string> get_type() const {
            return type;
        }

        const std::optional<Position> get_position() const {
            return position;
        }

        void set_type(const std::optional<std::string> _type) {
            type = _type;
        }
    private:
        std::string identifier;
        std::optional<std::string> type = std::nullopt;
        std::optional<Position> position;
    };
}
