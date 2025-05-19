#include "Controllable.hpp"
#include "raylib.h"
#include "utils/Log.hpp"

macro::component::Controllable::Controllable(Entity &e) : Component { e } {
}

macro::component::Controllable::~Controllable() {
  Log::d("Destroying component <Controllable>");
}

void macro::component::Controllable::update() {
  Log::d("CONTROLLABLE");

  for (auto &&trigger: _pressed_key_triggers) {
    if (IsKeyPressed(trigger.first)) {
      trigger.second(_entity);
    }
  }
}

void macro::component::Controllable::onKeyPressed(int k, std::function<void(Entity &)> const &&fn) {
  _pressed_key_triggers.emplace_back(std::make_pair(k, fn));
}
