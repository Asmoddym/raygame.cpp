#include "Application.hpp"
#include "raylib.h"
#include "utils/Log.hpp"
#include "utils/Timer.hpp"
#include "resource_dir.h"

macro::Application::Application() {
  Log::d("Constructing Application");

  InitWindow(1920, 1080, "raylib [core] example - 2d camera");
  SearchAndSetResourceDir("resources");
  SetTargetFPS(144);
}

macro::Application::~Application() {
  Log::d("Destroying Application");
}

void macro::Application::run() {
  Log::d("Running!");

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode2D(_scene.getCamera());
    IF_DEBUG(utils::Timer::reset());
    ClearBackground(BLACK);

    _scene.update();

    IF_DEBUG(Log::d("> ", utils::Timer::since(), "ms"));
    EndMode2D();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
}

