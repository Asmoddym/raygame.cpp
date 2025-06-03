#include "Draw.hpp"
#include "components.hpp"
#include "raylib.h"
#include <iostream>

void macro::system::Draw::update(macro::Registry &registry) {
  registry.forEach<component::Vector2, component::Texture>([&](int entity_id) {
    auto &position = registry.get<component::Vector2>(entity_id).value;
    auto &texture = registry.get<component::Texture>(entity_id).texture;

    std::cout << "coucou: " << entity_id << ", " << texture.id << std::endl;
    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
  });
}
