#pragma once

#include <neonc.h>
#include "../root.h"

namespace neonc {
    class Analyzer {
    public:
        Analyzer() = default;

        void analyze(std::shared_ptr<Node> root);
    };
}
