#include "Draw.h"

#include "component/Texture.h"
#include "component/Value.h"

void macro::system::Draw::update() {
  registry.forEach<component::Vector2, component::Texture>([&](Entity entity) {
    auto &position = entity.get<component::Vector2>().value;
    auto &texture = entity.get<component::Texture>().texture;

    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
  });
}
