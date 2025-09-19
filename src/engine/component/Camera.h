
#ifndef MACRO_COMPONENT_CAMERA_H_
# define MACRO_COMPONENT_CAMERA_H_

# include "Component.h"
# include "raylib.h"

namespace macro {
  namespace component {
    struct Camera : public Component {
      Camera2D camera;

      inline Camera(::Vector2 size) {
        camera.target = ::Vector2 { 0, 0 };
        camera.offset = ::Vector2 { size.x / 2, size.y / 2 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
      }
    };
  }
}

#endif //MACRO_COMPONENT_CAMERA_H_
