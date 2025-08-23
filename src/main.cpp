#include "engine/macro.h"

namespace rg {
  namespace system {
    class Raycast : public macro::System {
      private:
        Camera2D m_camera = { 0 };

      public:
        DefineSystem(Raycast, 16) {
          // m_camera.offset = ::Vector2 { size.x / 2.f, size.y / 2.f };
          m_camera.offset = ::Vector2 { 0, 0 };
          m_camera.rotation = 0.0f;
          m_camera.zoom = 1.0f;
        };

        inline virtual void update() override {
          BeginDrawing();
          ClearBackground(BLACK);
          BeginMode2D(m_camera);
          draw();
          EndMode2D();
          DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME);
          EndDrawing();
        }

      private:
        inline void draw() {
        }
    };
  }
}

int main() {
  macro::Application app;

  app.getSystemManager().set<rg::system::Raycast>();

  app.run();

  return 0;
}
