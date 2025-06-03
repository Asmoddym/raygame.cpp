#ifndef MACRO_LOG_H_
# define MACRO_LOG_H_

# include <iostream>
# include <sstream>

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
  
      template<typename... Args>
      static inline std::string to_s(Args&&... args) {
        std::stringstream ss;
  
        (append(ss, args), ...);
  
        return ss.str();
      }
  
    private:
      template<typename... Args>
      static inline void display(Args&&... args) {
        (output(args), ...);
        std::cout << std::endl;
      }
  
      template<typename T>
      static inline void output(T&& t) { std::cout << t; }
  
      template<typename T>
      static inline void append(std::stringstream &ss, T&& t) { ss << t; }
  };
}

#endif // MACRO_LOG_H_
