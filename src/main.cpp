#include "engine/Application.hpp"
#include "scene/MainScene.hpp"

int main() {
  Application app;

  app.run<MainScene>();

  return 0;
}
