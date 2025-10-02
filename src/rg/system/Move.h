#ifndef RG_SYSTEM_MOVE_H_
# define RG_SYSTEM_MOVE_H_

# include "rg/components.h"
# include "rg/enum/Direction.h"
# include "component/Camera.h"

namespace rg {
  namespace system {
    class Move: public macro::System {
      DefineSystem(Move, 16)

    public:
      inline virtual void update() override {
        registry.forEach<component::Controllable>(registry.bind(this, &Move::moveControllable));
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
        auto &cameraComponent = registry.get<macro::component::Camera>(0);
        e_Direction direction =  e_Direction::NONE;

        if (IsKeyDown(KEY_LEFT)) { rect.x -= 5; direction = e_Direction::LEFT; }
        if (IsKeyDown(KEY_RIGHT)) { rect.x += 5; direction = e_Direction::RIGHT; }
        if (IsKeyDown(KEY_UP)) { rect.y -= 5; direction = e_Direction::UP; }
        if (IsKeyDown(KEY_DOWN)) { rect.y += 5; direction = e_Direction::DOWN; }

        if (entity.has<macro::component::Sprite>()) {
          auto &sprite = entity.get<macro::component::Sprite>();

          if (sprite.getState() != direction) {
            sprite.setState(direction);
          }
        }

        cameraComponent.camera.target = ::Vector2 { rect.x, rect.y };
      }
    };
  }
}

#endif // !RG_SYSTEM_MOVE_H_
