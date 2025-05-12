#ifndef MACRO_UTILS_TIMER_HPP_
# define MACRO_UTILS_TIMER_HPP_

#include <chrono>

namespace macro {
  namespace utils {
    class Timer {
      public:
        static float since();
        static void reset();

      private:
        static inline std::chrono::time_point<std::chrono::steady_clock> _t;
    };
  }
}

#endif // MACRO_UTILS_TIMER_HPP_
