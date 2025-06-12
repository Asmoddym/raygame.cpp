#ifndef MACRO_LIB_CONCATENATE_H_
# define MACRO_LIB_CONCATENATE_H_

#include <sstream>
# include <string>

class Concatenator {
  public:
    Concatenator() = delete;
    virtual ~Concatenator() = delete;

    template<typename... Args>
    static inline std::string toString(Args&&... args) {
      std::stringstream ss;

      (append(ss, args), ...);

      return ss.str();
    }

  private:
    template<typename T>
      static inline void append(std::stringstream &ss, T&& t) { ss << t; }
};

# ifndef Concatenate
#  define Concatenate ::Concatenator::toString
# endif 

#endif //MACRO_LIB_CONCATENATE_H_
