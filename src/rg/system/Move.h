#ifndef RG_SYSTEM_MOVE_H_
# define RG_SYSTEM_MOVE_H_

#include "raylib.h"
# include "rg/components.h"
# include "component/Camera.h"

namespace rg {
  namespace system {
    class Move: public macro::System {
      DefineSystem(Move, 16);

    public:
      inline virtual void update() override {
        registry.forEach<component::Movable, component::Controllable>(registry.bind(this, &Move::moveControllable));
        registry.forEach<component::Movable, component::Velocity>(registry.bind(this, &Move::moveVelocity));
      }

      inline void moveVelocity(macro::Entity entity) {
        auto &r = entity.get<macro::component::Rectangle>().value;
        auto &v = entity.get<component::Velocity>().value;

        r.x += v.x;
        r.y += v.y;
      }

      inline void moveControllable(macro::Entity entity) {
        auto &rect = entity.get<macro::component::Rectangle>().value;

        if (entity.has<component::Controllable>()) {
          auto &cameraComponent = registry.get<macro::component::Camera>(0);

          if (IsKeyDown(KEY_LEFT)) { rect.x -= 5; }
          if (IsKeyDown(KEY_RIGHT)) { rect.x += 5; }
          if (IsKeyDown(KEY_UP)) { rect.y -= 5; }
          if (IsKeyDown(KEY_DOWN)) { rect.y += 5; }

          cameraComponent.camera.target = ::Vector2 { rect.x, rect.y };
        }
      }
    };
  }
}

#endif // !RG_SYSTEM_MOVE_H_
