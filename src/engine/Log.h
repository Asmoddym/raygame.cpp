#ifndef MACRO_LOG_H_
# define MACRO_LOG_H_

# include <iostream>
#include <ostream>

namespace macro {
  class Log {
    public:
      template<typename... Args>
      static inline void d(Args&&... args) {
        display(std::cout, "[DEBUG]  ", args...);
      }
  
      template<typename... Args>
      static inline void l(Args&&... args) {
        display(std::cout, "[LOG]  ", args...);
      }

      template<typename... Args>
      static inline void e(Args&&... args) {
        display(std::cerr, "[ERROR]  ", args...);
      }

      template<typename... Args>
      static inline void w(Args&&... args) {
        display(std::cout, "[WARNING]  ", args...);
      }
  
    private:
      template<typename... Args>
      static inline void display(std::ostream &stream, Args&&... args) {
        (output(stream, args), ...);
        stream << std::endl;
      }
  
      template<typename T>
      static inline void output(std::ostream &stream, T&& t) { stream << t; }
  };
}

# define PrintError ::macro::Log::e
# define PrintLog ::macro::Log::l
# define PrintWarning ::macro::Log::w

#endif // MACRO_LOG_H_
