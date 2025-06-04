#include "engine/macro.h"

class InputComponent : public macro::Component {};

class InputSystem : public macro::System {
  DefineSystem(InputSystem);

  public:
    inline virtual void update() override {
      registry.forEach<InputSystem>(registry.bind(this, &InputSystem::move));
    }

    inline void move(int entity_id) {
      auto &position = registry.get<macro::component::Vector2>(entity_id).value;
  
      if (IsKeyDown(KEY_LEFT)) { position.x -= 5; }
    }
};

int main() {
  macro::Application app;

  auto background_id = app.generateEntityID();
  app.getRegistry().set<macro::component::Vector2>(background_id, Vector2 { 0, 100 });
  app.getRegistry().set<InputComponent>(background_id);
  app.getRegistry().set<macro::component::Texture>(background_id, "wabbit_alpha.png");


  app.getSystemManager().set<InputSystem>();

  app.run();

  return 0;
}
