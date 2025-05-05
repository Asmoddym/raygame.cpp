#ifndef LOG_HPP_
# define LOG_HPP_

# include <iostream>
# include <sstream>

class Log {
  public:
    template<typename... Args>
#ifdef DEBUG
    static void d(Args&&... args) {
      display("[DEBUG]  ", args...);
    }
#else
    static void d(Args&&...) {}
#endif

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

#endif
