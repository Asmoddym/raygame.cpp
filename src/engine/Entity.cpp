#include "Entity.hpp"
#include "Component.hpp"
#include "Script.hpp"
#include "utils/Log.hpp"

void macro::Entity::update() {
  Log::d("Updating entity <", _id, ">");

  for (auto &&component: _components) {
    component->update();
  }

  for (auto &&script: _scripts) {
    script->update(*this);
  }
}
