#ifndef MACRO_COMPONENT_VALUE_HPP_
# define MACRO_COMPONENT_VALUE_HPP_

# include "Component.hpp"
#include "raylib.h"

namespace macro {
  namespace component {
    template<typename T> 
    struct Value : public Component {
      T value;

      Value(T const &v) : value { v } {}
    };

    typedef Value<::Vector2> Vector2;
  }
}

#endif //MACRO_COMPONENT_VALUE_HPP_
