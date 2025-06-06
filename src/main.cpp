#include "engine/macro.h"

using namespace macro;

class InputComponent : public Component {};
class ColliderComponent : public Component {
  public:
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
      auto &position = entity.get<component::Vector2>().value;
      auto &colliding = entity.get<ColliderComponent>().colliding;

      if (IsKeyDown(KEY_LEFT) && !colliding) { position.x -= 5; }
      if (IsKeyDown(KEY_RIGHT) && !colliding) { position.x += 5; }
      if (IsKeyDown(KEY_UP) && !colliding) { position.y -= 5; }
      if (IsKeyDown(KEY_DOWN) && !colliding) { position.y += 5; }
    }
};

class CollisionSystem : public System {
  DefineSystem(CollisionSystem);

  public:
  inline virtual void update() override {
    registry.forEach<component::Vector2, component::Texture>(registry.bind(this, &CollisionSystem::process));
  }

  inline void process(Entity entity) {
    if (entity.has<InputComponent>()) { return; }

    auto &position = entity.get<component::Vector2>().value;
    auto &texture = entity.get<component::Texture>().texture;
    auto &collider = entity.get<ColliderComponent>();

    registry.forEach<component::Vector2, component::Texture>([&](Entity other_entity) {
      if (other_entity.id == entity.id) { return; }

      auto &other_position = other_entity.get<component::Vector2>().value;
      auto &other_collider = other_entity.get<ColliderComponent>();

      if (other_position.y < position.y) {
        other_collider.colliding = true;
        other_collider.colliding_entity_id = entity.id;

        collider.colliding = true;
        collider.colliding_entity_id = other_entity.id;
      }
    });
  }
};

int main() {
  Application app;

  auto background = app.generateEntity();
  background
    .set<component::Vector2>(Vector2 { 0, 100 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<InputComponent>()
    .set<ColliderComponent>();

  auto npc = app.generateEntity();
  npc
    .set<component::Vector2>(Vector2 { -100, -100 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>();

  app.getSystemManager().set<InputSystem>();
  app.getSystemManager().set<CollisionSystem>();

  app.run();

  return 0;
}
