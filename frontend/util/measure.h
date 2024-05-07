#pragma once

#include <chrono>
#include <iostream>

class Measure {
private:
    std::chrono::steady_clock::time_point time;
public:
    Measure();

    void reset();
    void finish(std::string msg) const;
};
