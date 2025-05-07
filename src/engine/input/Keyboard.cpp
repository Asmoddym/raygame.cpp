#include "raylib.h"
#include "Keyboard.hpp"

bool macro::input::Keyboard::keyPressed(const int &key) {
  return IsKeyPressed(key);
}

bool macro::input::Keyboard::keyReleased(const int &key) {
  return IsKeyReleased(key);
}
