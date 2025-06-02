#include "Application.hpp"
#include "raylib.h"
#include "utils/Log.hpp"
#include "utils/Timer.hpp"
#include "resource_dir.h"

macro::Application::Application() : _entity_count { 1 } {
  Log::d("Constructing Application");

  InitWindow(1920, 1080, "raylib [core] example - 2d camera");
  SearchAndSetResourceDir("resources");
  SetTargetFPS(144);

  _camera.offset = Vector2 { 1920/2.0f, 1080/2.0f };
  _camera.rotation = 0.0f;
  _camera.zoom = 1.0f;
}

macro::Application::~Application() {
  Log::d("Destroying Application");
}

void macro::Application::run() {
  Log::d("Running!");

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode2D(_camera);
    IF_DEBUG(utils::Timer::reset());
    ClearBackground(BLACK);

    _system_manager.update(_component_manager);

    IF_DEBUG(Log::d("> ", utils::Timer::since(), "ms"));
    EndMode2D();
    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
}

int macro::Application::generateEntityID() {
  return _entity_count++;
}
