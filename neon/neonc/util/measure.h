#pragma once

#include <neonc.h>

namespace neonc {
    class Measure {
    private:
        std::chrono::steady_clock::time_point time;
    public:
        Measure();

        void reset();
        void finish(std::string msg) const;
    };
}
