#include "engine/macro.h"
#include "raylib.h"
#include "system/Draw.h"

using namespace macro;

class InputComponent : public Component {};

typedef component::Value<Vector2> ColliderComponent;

class InputSystem : public System {
  DefineSystem(InputSystem);

  public:
    inline virtual void update() override {
      registry.forEach<InputComponent>(registry.bind(this, &InputSystem::move));
    }

    inline void move(Entity entity) {
      auto &rectangle = entity.get<component::Value<::Rectangle>>().value;

      // TODO: move the condition in CollisionSystem
      if (IsKeyDown(KEY_LEFT)) { rectangle.x -= 5; }
      if (IsKeyDown(KEY_RIGHT)) { rectangle.x += 5; }
      if (IsKeyDown(KEY_UP)) { rectangle.y -= 5; }
      if (IsKeyDown(KEY_DOWN)) { rectangle.y += 5; }
    }
};

class CollisionSystem : public System {
  DefineSystem(CollisionSystem);

  bool _show_bounds = false;

  public:
    inline virtual void update() override {
      if (IsKeyPressed(KEY_B)) {
        _show_bounds = !_show_bounds;
      }

      registry.forEach<component::Value<::Rectangle>, ColliderComponent>(registry.bind(this, &CollisionSystem::process));
    }

    inline void process(Entity entity) {
      auto &rectangle = entity.get<component::Value<::Rectangle>>().value;
      auto &texture = entity.get<component::Texture>().texture;
      auto &collider = entity.get<ColliderComponent>().value;
      bool colliding = false;

      registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity other_entity) {
        if (other_entity.id == entity.id) { return; }

        auto &other_rectangle = other_entity.get<component::Value<::Rectangle>>().value;
        auto &other_collider = other_entity.get<ColliderComponent>().value;

        if (CheckCollisionRecs(rectangle, other_rectangle)) {
          if (_show_bounds) { DrawRectangleLinesEx(other_rectangle, 2, YELLOW); }

          //TODO: find a better way to handle this, maybe just remove it for now?
          colliding = true;
        } else {
          if (_show_bounds) { DrawRectangleLinesEx(other_rectangle, 1, GREEN); }
        }
      });

      if (colliding) {
        rectangle.x = collider.x;
        rectangle.y = collider.y;
      } else {
        collider.x = rectangle.x;
        collider.y = rectangle.y;
      }
    }
};

int main() {
  Application app;

  auto background = app.generateEntity();
  background
    //TODO: override this to improve constructor
    .set<component::Value<::Rectangle>>(::Rectangle { 0, 100, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<InputComponent>()
    .set<ColliderComponent>(Vector2 { 0, 100 });

  auto npc = app.generateEntity();
  npc
    .set<component::Value<::Rectangle>>(::Rectangle { -100, -100, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>(Vector2 { -100, -100 });

  app.getSystemManager().set<InputSystem>();
  app.getSystemManager().set<CollisionSystem>();

  app.run();

  return 0;
}
