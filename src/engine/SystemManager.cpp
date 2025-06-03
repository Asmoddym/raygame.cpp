#include "SystemManager.hpp"

#include "system/Draw.hpp"

macro::SystemManager::SystemManager(macro::Registry &registry) : _registry { registry } {
  set<system::Draw>();
}

macro::SystemManager::~SystemManager() {
  for (auto &&s: _systems) {
    delete s;
  }
}

void macro::SystemManager::update() {
  for (auto &&system: _systems) {
    system->update();
  }
}
