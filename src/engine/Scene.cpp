#include "Scene.hpp"
#include "utils/Log.hpp"

macro::Scene::Scene(std::string const &name) : _name { name } {
  Log::d("Constructing <", _name, ">");
}

macro::Scene::~Scene() {
  Log::d("Destroying <", _name, ">");
}

