#include "engine/macro.h"

class InputComponent : public macro::Component {};
class ColliderComponent : public macro::Component {
  public:
    bool colliding = false;
    int colliding_entity = -1;
};

class InputSystem : public macro::System {
  DefineSystem(InputSystem);

  public:
    inline virtual void update() override {
      registry.forEach<InputComponent>(registry.bind(this, &InputSystem::move));
    }

    inline void move(int entity_id) {
      auto &position = registry.get<macro::component::Vector2>(entity_id).value;
      auto &colliding = registry.get<ColliderComponent>(entity_id).colliding;

      if (IsKeyDown(KEY_LEFT) && !colliding) { position.x -= 5; }
      if (IsKeyDown(KEY_RIGHT) && !colliding) { position.x += 5; }
      if (IsKeyDown(KEY_UP) && !colliding) { position.y -= 5; }
      if (IsKeyDown(KEY_DOWN) && !colliding) { position.y += 5; }
    }
};

class CollisionSystem : public macro::System {
  DefineSystem(CollisionSystem);

  public:
  inline virtual void update() override {
    registry.forEach<macro::component::Vector2, macro::component::Texture>(registry.bind(this, &CollisionSystem::process));
  }

  inline void process(int entity_id) {
    if (registry.has<InputComponent>(entity_id)) { return; }

    auto &position = registry.get<macro::component::Vector2>(entity_id).value;
    auto &texture = registry.get<macro::component::Texture>(entity_id).texture;
    auto &collider = registry.get<ColliderComponent>(entity_id);

    registry.forEach<macro::component::Vector2, macro::component::Texture>([&](int other_entity_id) {
      if (other_entity_id == entity_id) { return; }

      auto &other_position = registry.get<macro::component::Vector2>(other_entity_id).value;
      auto &other_collider = registry.get<ColliderComponent>(other_entity_id);

      if (other_position.y < position.y) {
        other_collider.colliding = true;
        other_collider.colliding_entity = entity_id;

        collider.colliding = true;
        collider.colliding_entity = other_entity_id;
      }
    });
  }
};

int main() {
  macro::Application app;

  auto background_id = app.generateEntityID();
  app.getRegistry()
    .set<macro::component::Vector2>(background_id, Vector2 { 0, 100 })
    .set<macro::component::Texture>(background_id, "wabbit_alpha.png")
    .set<InputComponent>(background_id)
    .set<ColliderComponent>(background_id);

  auto test = app.generateEntityID();
  app.getRegistry()
    .set<macro::component::Vector2>(test, Vector2 { -100, -100 })
    .set<macro::component::Texture>(test, "wabbit_alpha.png")
    .set<ColliderComponent>(test);

  app.getSystemManager().set<InputSystem>();
  app.getSystemManager().set<CollisionSystem>();

  app.run();

  return 0;
}
