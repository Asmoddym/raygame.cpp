#ifndef MACRO_LIB_TIMER_H_
# define MACRO_LIB_TIMER_H_

# include <chrono>

class Timer {
  public:
    static inline double since() {
      double elapsed = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - Timer::_t).count();
      reset();

      return elapsed / 1000000;
    }

    static inline void reset() {
      _t = std::chrono::steady_clock::now();
    }

  private:
    static inline std::chrono::time_point<std::chrono::steady_clock> _t;
};

#endif // MACRO_LIB_TIMER_H_
