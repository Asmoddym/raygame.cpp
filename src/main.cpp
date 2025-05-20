#include "engine/macro.hpp"

class PlayerScript : public macro::Script {
  public:
    void initialize(macro::Entity &e) override {
      e.addComponent<macro::component::Drawable>("wabbit_alpha.png");
    }

    virtual void update(macro::Entity &e) override {
      if (IsKeyDown(KEY_RIGHT)) {
        e.getPosition().x += 5;
      }
      if (IsKeyDown(KEY_LEFT)) {
        e.getPosition().x -= 5;
      }
      if (IsKeyDown(KEY_UP)) {
        e.getPosition().y -= 5;
      }
      if (IsKeyDown(KEY_DOWN)) {
        e.getPosition().y += 5;
      }

      e.updateCameraTarget(e.getPosition());
    }
};

int main() {
  macro::Application app;

  auto &scene = app.initializeScene("Main");
  auto &player = scene.createEntity("coucou");
  player.addScript<PlayerScript>();

  app.run();

  return 0;
}
