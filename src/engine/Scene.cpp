#include "Scene.hpp"
#include "utils/Log.hpp"

macro::Scene::Scene() : _entity_count { 0 } {
  _camera.offset = Vector2 { 1920/2.0f, 1080/2.0f };
  _camera.rotation = 0.0f;
  _camera.zoom = 1.0f;
}

macro::Scene::~Scene() {
}

void macro::Scene::update() {
  Log::d("Updating scene (", _components.size(), " components)");
}
