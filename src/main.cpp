#include "engine/component/Value.hpp"
#include "engine/macro.hpp"

using namespace macro;

int main() {
  Application app;
  auto &scene = app.getScene();

  auto background = scene.createEntity();
  background.addComponent<component::Vector2>(Vector2 { 0, 12 });
  background.addComponent<component::Texture>("wabbit_alpha.png");

  macro::Log::d(background.getComponent<component::Vector2>().value.x);
  app.run();

  return 0;
}
