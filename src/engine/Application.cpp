#include "Application.hpp"
#include "raylib.h"
#include "utils/Log.hpp"
#include "utils/Timer.hpp"
#include "resource_dir.h"

macro::Application::Application() : _entity_count { 1 }, _camera { 0 } {
  Log::d("Constructing Application");

  Vector2 size = Vector2 { 1920, 1080 };

  InitWindow((int)size.x, (int)size.y, "raylib [core] example - 2d camera");
  SearchAndSetResourceDir("resources");
  SetTargetFPS(144);

  _camera.offset = ::Vector2 { size.x / 2.f, size.y / 2.f };
  _camera.rotation = 0.0f;
  _camera.zoom = 1.0f;
}

macro::Application::~Application() {
  Log::d("Destroying Application");
}

void macro::Application::run() {
  Log::d("Running!");

  while (!WindowShouldClose()) {
    DebugLog(_camera.offset.x, ", ", _camera.offset.y);
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
