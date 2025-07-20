#ifndef MACRO_LIB_TIMER_H_
# define MACRO_LIB_TIMER_H_

# include <chrono>

class Timer {
  public:
    static inline double since() {
      double elapsed = (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - Timer::m_t).count();

      return elapsed / 1000000;
    }

    static inline void reset() {
      m_t = std::chrono::steady_clock::now();
    }

  private:
    static inline std::chrono::time_point<std::chrono::steady_clock> m_t;
};

#endif // MACRO_LIB_TIMER_H_
