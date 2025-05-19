#include "engine/component/Drawable.hpp"
#include "engine/macro.hpp"
#include "raylib.h"

class TestScript : public macro::Script {
  public:
    void initialize(macro::Entity &e) override {
      e.addComponent<macro::component::Drawable>("wabbit_alpha.png");
    }

    virtual void update(macro::Entity &e) override {
      if (IsKeyPressed(KEY_RIGHT)) {
        e.getPosition().x += 20;
      }
      if (IsKeyPressed(KEY_LEFT)) {
        e.getPosition().x -= 20;
      }
      if (IsKeyPressed(KEY_UP)) {
        e.getPosition().y -= 20;
      }
      if (IsKeyPressed(KEY_DOWN)) {
        e.getPosition().y += 20;
      }
    }
};

int main() {
  macro::Application app;

  auto &scene = app.initializeScene("Main");
  auto &entity = scene.createEntity("coucou");
  entity.addScript<TestScript>();
  
  app.run();

  return 0;
}
