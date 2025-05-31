#include "engine/macro.hpp"

using namespace macro;

int main() {
  Application app;
  auto &scene = app.getScene();

  auto background = scene.createEntity();
  background.addComponent<component::Value<Vector2>>(Vector2 { 0, 12 });

  Log::d(background.getComponent<component::Value<Vector2>>().value.y);
  app.run();

  return 0;
}
