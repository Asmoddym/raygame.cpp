#ifndef MACRO_SYSTEM_DRAW_H_
# define MACRO_SYSTEM_DRAW_H_

# include "System.h"
# include "component/Camera.h"
# include "component/Sprite.h"
# include "component/Texture.h"
# include "component/Rectangle.h"
# include "lib/Timer.h"
# include "raylib.h"
# include "raygui.h"

namespace macro {
  namespace system {
    class Draw : public System {
      private:
        Camera2D &m_camera;

      public:
        DefineSystemWithAdditionalInitializes(Draw, UPDATE_EACH_FRAME, m_camera { registry.get<component::Camera>(0).camera });

        inline virtual void update() override {
          auto since = Timer::since();
          Timer::reset();

          BeginDrawing();
          ClearBackground(BLACK);
          BeginMode2D(m_camera);

          registry.forEach<component::Rectangle, component::Texture>([&](Entity entity) {
              auto &rect = entity.get<component::Rectangle>().value;
              auto &texture = entity.get<component::Texture>().texture;

              DrawTexture(texture, (int)rect.x, (int)rect.y, WHITE);
          });

          registry.forEach<component::Rectangle, component::Sprite>([&](Entity entity) {
              auto &sprite = entity.get<component::Sprite>();
              auto &rect = entity.get<component::Rectangle>().value;

              sprite.draw(rect);
          });

          auto render_time = Timer::since();

          EndMode2D();
          if (GuiButton(Rectangle{ 24, 24, 120, 30 }, "#191#Show Message")) { exit(1); }
          DrawText(TextFormat("%d FPS\n%.03fms compute\n%.03fms render", GetFPS(), since, render_time), 10, 10, 20, LIME);
          EndDrawing();
        }
    };
  }
}

#endif //MACRO_SYSTEM_DRAW_H_
