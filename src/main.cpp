#include "engine/macro.hpp"

int main() {
  macro::Application app;

  auto &scene = app.initializeScene("Main");
  auto &entity = scene.createEntity("coucou");
  entity.addComponent<macro::component::Drawable>("wabbit_alpha.png");

  app.run();

  return 0;
}
