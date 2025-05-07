#include "engine/Application.hpp"
#include "scene/MainScene.hpp"

int main() {
  macro::Application app;

  app.run<MainScene>();

  return 0;
}
