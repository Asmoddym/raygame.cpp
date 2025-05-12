#include "Drawable.hpp"
#include "raylib.h"
#include "utils/Log.hpp"

macro::component::Drawable::Drawable(std::string const &path) {
  _texture = LoadTexture(path.c_str());
}

macro::component::Drawable::~Drawable() {
  Log::d("Destroying component <Drawable>");

  UnloadTexture(_texture);
}

void macro::component::Drawable::update() {
  Log::d("DRAXABLE");
  DrawTexture(_texture, 0, 0, WHITE);
}
