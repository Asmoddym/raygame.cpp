#include "Scene.hpp"
#include "utils/Log.hpp"

macro::Scene::Scene() : _initialized { false } {
  _camera.offset = Vector2 { 1920/2.0f, 1080/2.0f };
  _camera.rotation = 0.0f;
  _camera.zoom = 1.0f;
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
}

void macro::Scene::update() {
  Log::d("[Scene <", _name, ">] Updating scene <", _name, "> (", _components.size(), " components)");
}
