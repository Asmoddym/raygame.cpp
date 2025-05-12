#include "Application.hpp"
#include "raylib.h"
#include "utils/Log.hpp"
#include "utils/Timer.hpp"

macro::Application::Application() {
  Log::d("Constructing Application");
}

macro::Application::~Application() {
  Log::d("Destroying Application");
}

void macro::Application::run() {
  Log::d("Running!");

  InitWindow(640, 480, "raylib [core] example - 2d camera");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    IF_DEBUG(utils::Timer::reset());

    _scene_manager.getCurrentScene()->update();

    BeginDrawing();

    IF_DEBUG(Log::d("> ", utils::Timer::since(), "ms"));
    EndDrawing();
  }

  CloseWindow();
}

