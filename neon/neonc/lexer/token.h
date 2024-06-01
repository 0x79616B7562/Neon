#pragma once

#include "../util/clicolor.h"
#include "../types/tokenid.h"
#include <neonc.h>
#include "../types/position.h"

namespace neonc {
    struct Token {
        void dump() const;

        const TokenId token;
        const std::string value;

        const Position position;
    };
}
