#include "Component.hpp"
#include "engine/macro.hpp"

// class PlayerScript : public macro::Script {
//   DefineMacroScript(PlayerScript);
//
//   public:
//     void initialize() override {
//       owner.addComponent<macro::component::Drawable>("wabbit_alpha.png");
//     }
//
//     virtual void update() override {
//       if (IsKeyDown(KEY_RIGHT)) {
//         owner.getPosition().x += 5;
//       }
//       if (IsKeyDown(KEY_LEFT)) {
//         owner.getPosition().x -= 5;
//       }
//       if (IsKeyDown(KEY_UP)) {
//         owner.getPosition().y -= 5;
//       }
//       if (IsKeyDown(KEY_DOWN)) {
//         owner.getPosition().y += 5;
//       }
//
//       owner.getScene().getCamera().target = owner.getPosition();
//     }
// };
//
// class BackgroundScript : public macro::Script {
//   DefineMacroScript(BackgroundScript);
//
//   int tiles_x = 50;
//   int tiles_y = 50;
//   Texture2D _texture;
//
//   public:
//   virtual void initialize() override {
//     _texture = LoadTexture("wabbit_alpha.png");
//   }
//
//   virtual void update() override {
//     for (int y = 0; y < tiles_y; y++) {
//       for (int x = 0; x < tiles_x; x++) {
//         DrawTexture(_texture, x * 64, y * 64, WHITE);
//       }
//     }
//   }
// };
//

class Position : public macro::Component {
  public:
    Vector2 position;

  Position(Vector2 v) : position { v } {}
  virtual ~Position() override {}
};

int main() {
  macro::Application app;

  auto &scene = app.initializeScene("Main");
  int background_id = scene.createEntity();

  scene.addComponent<Position>(background_id, Vector2 { 0, 12 });

  macro::Log::d(scene.getComponent<Position>(background_id).position.y);

  exit(1);

  // auto &player = scene.createEntity();
  //
  // player.addScript<PlayerScript>();
  // background.addScript<BackgroundScript>();
  //
  app.run();

  return 0;
}
