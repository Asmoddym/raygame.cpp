#ifndef MACRO_COMPONENT_TEXTURE_H_
# define MACRO_COMPONENT_TEXTURE_H_

# include "Component.h"
# include "raylib.h"
# include <string>

namespace macro {
  namespace component {
    struct Texture : public Component {
      Texture2D texture;

      inline Texture(std::string const &path) : texture { LoadTexture(path.c_str()) } {}
      inline virtual ~Texture() override { UnloadTexture(texture); };
    };
  }
}

#endif //MACRO_COMPONENT_TEXTURE_H_
