#include "Scene.hpp"
#include "utils/Log.hpp"

macro::Scene::Scene() : _initialized { false } {
}

macro::Scene::~Scene() {
  Log::d("Destroying scene <", _name, ">");
}

void macro::Scene::initialize(std::string const &name) {
  _initialized = true;
  _name = name;
}

void macro::Scene::destroy() {
  _initialized = false;

  _name = "";
  _entities.clear();
}

void macro::Scene::update() {
  Log::d("[Scene <", _name, ">] Updating scene <", _name, "> (", _entities.size(), " entities)");

  for (auto &&entity: _entities) {
    entity.second.update();
  }
}
