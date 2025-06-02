#include "SystemManager.hpp"

void macro::SystemManager::update(macro::Registry &registry) {
  for (auto &&system: _systems) {
    system->update(registry);
  }
}
