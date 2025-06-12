#ifndef MACRO_LOG_H_
# define MACRO_LOG_H_

# include <iostream>

namespace macro {
  class Log {
    public:
      template<typename... Args>
      static inline void d(Args&&... args) {
        display("[DEBUG]  ", args...);
      }
  
      template<typename... Args>
      static inline void l(Args&&... args) {
        display("[LOG]  ", args...);
      }
  
    private:
      template<typename... Args>
      static inline void display(Args&&... args) {
        (output(args), ...);
        std::cout << std::endl;
      }
  
      template<typename T>
      static inline void output(T&& t) { std::cout << t; }
  };
}

#endif // MACRO_LOG_H_
