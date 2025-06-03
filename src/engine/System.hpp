#ifndef MACRO_SYSTEM_HPP_
# define MACRO_SYSTEM_HPP_

#include "Registry.hpp"

namespace macro {
  class System {
    public:
      System() {}
      virtual ~System() {}

      virtual void update(Registry &registry) = 0;
  };
}

#endif //MACRO_SYSTEM_HPP_
