#include "Scene.hpp"
#include "utils/Log.hpp"

Scene::Scene(std::string const &name) : _name { name } {
  Log::d("Constructing <", _name, ">");
}

Scene::~Scene() {
  Log::d("Destroying <", _name, ">");
}

