#include "Application.h"
#include "Debug.h"
#include "raylib.h"
#include "resource_dir.h"

#include "lib/Timer.h"
#include "component/Camera.h"

macro::Application::Application() {
  DebugLog("Constructing Application");

  Vector2 size = Vector2 { 1280, 720 };

  // Taken from https://github.com/raysan5/raylib/discussions/2999, basically OSX has a weird way through HigpDPI to handle their resolutions
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow((int)size.x, (int)size.y, "raylib [core] example - 2d camera");
  SearchAndSetResourceDir("resources");

  generateEntity().set<component::Camera>(size);
}

void macro::Application::run() {
  Log::d("Running!");

  while (!WindowShouldClose()) {
    Timer::reset();
    m_systemManager.update();
  }

  CloseWindow();
}

