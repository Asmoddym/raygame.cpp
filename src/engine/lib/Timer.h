#ifndef MACRO_LIB_TIMER_H_
# define MACRO_LIB_TIMER_H_

# include <chrono>

class Timer {
  public:
    static inline float since() {
      float elapsed = (float)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - Timer::_t).count();
      reset();

      return elapsed / 1000;
    }

    static inline void reset() {
      _t = std::chrono::steady_clock::now();
    }

  private:
    static inline std::chrono::time_point<std::chrono::steady_clock> _t;
};

#endif // MACRO_LIB_TIMER_H_
