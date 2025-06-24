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

  // Taken from https://github.com/raysan5/raylib/discussions/2999
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow((int)size.x, (int)size.y, "raylib [core] example - 2d camera");
  SearchAndSetResourceDir("resources");
  SetTargetFPS(144);

  m_camera.offset = ::Vector2 { size.x / 2.f, size.y / 2.f };
  m_camera.rotation = 0.0f;
  m_camera.zoom = 1.0f;

  m_systemManager.set<system::Draw>();
}

void macro::Application::run(bool server) {
  Log::d("Running!");

  if (server) {
    m_server.run();
  } else {
    m_client.run();
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    BeginMode2D(m_camera);

    DebugIf(Timer::reset());

    ClearBackground(BLACK);
    m_systemManager.update();

    EndMode2D();
    DebugIf(DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME));
    EndDrawing();
  }

  CloseWindow();
}

