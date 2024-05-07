#include "measure.h"
#include <chrono>

Measure::Measure() {
    time = std::chrono::steady_clock::now();
}

void Measure::reset() {
    time = std::chrono::steady_clock::now();
}

void Measure::finish(std::string msg) const {
    auto end = std::chrono::steady_clock::now();

    std::cout << msg << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - time).count() << " ms" << std::endl;
}
