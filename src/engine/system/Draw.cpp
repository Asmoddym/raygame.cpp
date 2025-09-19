#include "Draw.h"

#include "component/Texture.h"
#include "component/Rectangle.h"

#include "lib/Concatenate.h"
#include "lib/Timer.h"

void macro::system::Draw::update() {
  BeginDrawing();
  ClearBackground(BLACK);
  BeginMode2D(m_camera);

  registry.forEach<component::Rectangle, component::Texture>([&](Entity entity) {
    auto &rect = entity.get<component::Rectangle>().value;
    auto &texture = entity.get<component::Texture>().texture;

    DrawTexture(texture, (int)rect.x, (int)rect.y, WHITE);
  });

  EndMode2D();
  DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME);
  EndDrawing();
}
