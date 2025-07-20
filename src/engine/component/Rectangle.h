#ifndef MACRO_COMPONENT_RECTANGLE_H_
# define MACRO_COMPONENT_RECTANGLE_H_

# include "Component.h"
# include "raylib.h"

namespace macro {
  namespace component {
    struct Rectangle : public Component {
      ::Rectangle value;

      inline Rectangle(float x, float y, int width, int height) : value { ::Rectangle { x, y, (float)width, (float)height } } {}
      inline Rectangle(::Rectangle const &rect) : value { rect } {}
      inline virtual ~Rectangle() override { };

      inline float x() { return value.x; }
      inline float y() { return value.y; }
      inline float height() { return value.height; }
      inline float width() { return value.width; }
    };
  }
}

#endif //MACRO_COMPONENT_RECTANGLE_H_
