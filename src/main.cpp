#include "engine/Application.hpp"
#include "scene/MainScene.hpp"

int main() {
  macro::Application app;

  app.registerMainScene<MainScene>();
  app.run();

  return 0;
}
