#include "Draw.h"

#include "component/Texture.h"
#include "component/Value.h"

void macro::system::Draw::update() {
  registry.forEach<component::Value<::Rectangle>, component::Texture>([&](Entity entity) {
    auto &rect = entity.get<component::Value<::Rectangle>>().value;
    auto &texture = entity.get<component::Texture>().texture;

    DrawTexture(texture, (int)rect.x, (int)rect.y, WHITE);
  });
}
