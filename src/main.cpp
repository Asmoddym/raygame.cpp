#include "engine/macro.h"

class Test : public macro::System {
  DefineSystem(Test);

  public:
    inline virtual void update() override {
      //TODO: Maybe create an Entity class to make something like `entity.get<Vector2>`?
      registry.forEach<macro::component::Vector2>([&](int entity_id) {
        auto &position = registry.get<macro::component::Vector2>(entity_id).value;

        if (IsKeyDown(KEY_LEFT)) { position.x -= 5; }
      });
    }
};

int main() {
  macro::Application app;

  auto background_id = app.generateEntityID();
  app.getRegistry().set<macro::component::Vector2>(background_id, Vector2 { 0, 100 });
  app.getRegistry().set<macro::component::Texture>(background_id, "wabbit_alpha.png");


  app.getSystemManager().set<Test>();

  app.run();

  return 0;
}
