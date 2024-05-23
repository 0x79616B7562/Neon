#pragma once

#include "token.h"
#include "../util/extract_from_file.h"
#include <neonc.h>

namespace neonc {
    class Lexer {
    public:
        Lexer() = default;

        const std::vector<Token> Tokenize(const std::string file_path, std::string input) const;
    };
}
