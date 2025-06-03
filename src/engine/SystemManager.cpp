#include "SystemManager.hpp"
#include "System.hpp"
#include "system/Draw.hpp"

macro::SystemManager::SystemManager() {
  set<system::Draw>();
}

macro::SystemManager::~SystemManager() {
  for (auto &&s: _systems) {
    delete s;
  }
}

void macro::SystemManager::update(macro::Registry &registry) {
  for (auto &&system: _systems) {
    system->update(registry);
  }
}
