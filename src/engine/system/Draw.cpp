#include "Draw.h"

#include "component/Texture.h"
#include "component/Rectangle.h"
#include "lib/Timer.h"

void macro::system::Draw::update() {
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

  auto render_time = Timer::since();

  EndMode2D();
  DrawText(TextFormat("%d FPS\n%.03fms compute\n%.03fms render", GetFPS(), since, render_time), 10, 10, 20, LIME);
  EndDrawing();
}
