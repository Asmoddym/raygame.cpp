#include "Application.h"
#include "Debug.h"
#include "raylib.h"
#include "resource_dir.h"

#include "lib/Timer.h"
#include "lib/Concatenate.h"

#include "system/Draw.h"

macro::Application::Application() {
  DebugLog("Constructing Application");

  Vector2 size = Vector2 { 1280, 720 };

  InitWindow((int)size.x, (int)size.y, "raylib [core] example - 2d camera");
  SearchAndSetResourceDir("resources");
  SetTargetFPS(144);

  _camera.offset = ::Vector2 { size.x / 2.f, size.y / 2.f };
  _camera.rotation = 0.0f;
  _camera.zoom = 1.0f;

  _system_manager.set<system::Draw>();
}

void macro::Application::run() {
  Log::d("Running!");

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode2D(_camera);

    DebugIf(Timer::reset());

    ClearBackground(BLACK);
    _system_manager.update();

    EndMode2D();
    DebugIf(DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME));
    EndDrawing();
  }

  CloseWindow();
}

