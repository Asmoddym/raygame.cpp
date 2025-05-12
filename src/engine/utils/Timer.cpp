#include "Timer.hpp"
#include <chrono>

float macro::utils::Timer::since() {
  float elapsed = (float)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - Timer::_t).count();
  Timer::reset();

  return elapsed / 1000;
}

void macro::utils::Timer::reset() {
  Timer::_t = std::chrono::steady_clock::now();
}
