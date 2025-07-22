#ifndef MACRO_COMPONENT_VALUE_H_
# define MACRO_COMPONENT_VALUE_H_

# include "Component.h"
# include "raylib.h"

# define DefineValueComponent(Name, type) struct Name : ::macro::component::Value<type> { \
  inline Name(type v) : Value { v } {} \
  inline virtual ~Name() {} \
}; 

namespace macro {
  namespace component {
    template<typename T> 
    struct Value : public Component {
      T value;

      inline Value(T const &v) : value { v } {}
      inline virtual ~Value() {}
    };

    typedef Value<::Vector2> Vector2;
  }
}

#endif //MACRO_COMPONENT_VALUE_H_
