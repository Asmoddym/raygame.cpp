#include "Draw.h"

#include "component/Texture.h"
#include "component/Value.h"

void macro::system::Draw::update() {
  registry.forEach<component::Vector2, component::Texture>([&](int entity_id) {
    auto &position = registry.get<component::Vector2>(entity_id).value;
    auto &texture = registry.get<component::Texture>(entity_id).texture;

    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
  });
}
