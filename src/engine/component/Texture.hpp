#ifndef MACRO_COMPONENT_TEXTURE_HPP_
# define MACRO_COMPONENT_TEXTURE_HPP_

# include "Component.hpp"
#include "raylib.h"
#include <string>

namespace macro {
  namespace component {
    struct Texture : public Component {
      Texture2D texture;

      Texture(std::string const &path) : texture { LoadTexture(path.c_str()) } {}
    };
  }
}

#endif //MACRO_COMPONENT_TEXTURE_HPP_
