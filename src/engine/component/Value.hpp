#ifndef MACRO_COMPONENT_VALUE_HPP_
# define MACRO_COMPONENT_VALUE_HPP_

# include "Component.hpp"

namespace macro {
  namespace component {
    template<typename T> 
    struct Value : public Component {
      T value;

      Value(T const &v) : value { v } {}
    };
  }
}

#endif //MACRO_COMPONENT_VALUE_HPP_
