#ifndef MACRO_LOG_HPP_
# define MACRO_LOG_HPP_

# include <iostream>
# include <sstream>

# include "Debug.hpp"

namespace macro {
  class Log {
    public:
      template<typename... Args>
      static void d(Args&&... args) {
        IF_DEBUG({
            display("[DEBUG]  ", args...);
            });
      }
  
      template<typename... Args>
      static void l(Args&&... args) {
        display("[LOG]  ", args...);
      }
  
      template<typename... Args>
      static std::string to_s(Args&&... args) {
        std::stringstream ss;
  
        (append(ss, args), ...);
  
        return ss.str();
      }
  
    private:
      template<typename... Args>
      static void display(Args&&... args) {
        (output(args), ...);
        std::cout << std::endl;
      }
  
      template<typename T>
      static void output(T&& t) { std::cout << t; }
  
      template<typename T>
      static void append(std::stringstream &ss, T&& t) { ss << t; }
  };
}

#endif // MACRO_LOG_HPP_
