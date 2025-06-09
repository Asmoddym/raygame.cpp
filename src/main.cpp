#include "engine/macro.h"
#include "raylib.h"

using namespace macro;

class InputComponent : public Component {};
class ColliderComponent : public Component {
  public:
    Vector2 previous_position;
    bool colliding = false;
    int colliding_entity_id = -1;
};

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

  public:
  inline virtual void update() override {
    registry.forEach<component::Value<::Rectangle>, ColliderComponent>(registry.bind(this, &CollisionSystem::process));
  }

  inline void process(Entity entity) {
    auto &rectangle = entity.get<component::Value<::Rectangle>>().value;
    auto &texture = entity.get<component::Texture>().texture;
    auto &collider = entity.get<ColliderComponent>();

    registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity other_entity) {
        auto &other_rectangle = other_entity.get<component::Value<::Rectangle>>().value;
        DrawRectangleLinesEx(other_rectangle, 1, RED);

        if (other_entity.id == entity.id) { return; }

        auto &other_collider = other_entity.get<ColliderComponent>();

        if (CheckCollisionRecs(rectangle, other_rectangle)) {
          DrawRectangleLinesEx(other_rectangle, 2, GREEN);
          collider.colliding = true;
        }
    });

    if (collider.colliding) {
      rectangle.x = collider.previous_position.x;
      rectangle.y = collider.previous_position.y;
      collider.colliding = false;
    } else {
      collider.previous_position.x = rectangle.x;
      collider.previous_position.y = rectangle.y;
    }
  }
};

int main() {
  Application app;

  auto background = app.generateEntity();
  background
    .set<component::Value<::Rectangle>>(::Rectangle { 0, 100, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<InputComponent>()
    .set<ColliderComponent>();

  auto npc = app.generateEntity();
  npc
    .set<component::Value<::Rectangle>>(::Rectangle { -100, -100, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>();

  app.getSystemManager().set<InputSystem>();
  app.getSystemManager().set<CollisionSystem>();

  app.run();

  return 0;
}
