#ifndef MACRO_COMPONENT_DRAWABLE_HPP_
# define MACRO_COMPONENT_DRAWABLE_HPP_

#include "Component.hpp"
#include "raylib.h"
#include <string>

namespace macro {
  namespace component {
    class Drawable : public Component {
      private:
        Texture2D _texture;

      public:
        Drawable(Entity &e, std::string const &path);
        virtual ~Drawable() override;

        virtual void update() override;
    };
  }
}

#endif // MACRO_COMPONENT_DRAWABLE_HPP_
