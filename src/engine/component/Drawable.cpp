#include "Entity.hpp"
#include "Drawable.hpp"
#include "raylib.h"
#include "utils/Log.hpp"

macro::component::Drawable::Drawable(Entity &e, std::string const &path) : Component { e } {
  _texture = LoadTexture(path.c_str());
}

macro::component::Drawable::~Drawable() {
  Log::d("Destroying component <Drawable>");

  UnloadTexture(_texture);
}

void macro::component::Drawable::update() {
  Log::d("DRAWABLE");

  DrawTexture(_texture, (int)_entity.getPosition().x, (int)_entity.getPosition().y, WHITE);
}
