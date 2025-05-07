#include "Entity.hpp"
#include "utils/Log.hpp"

void macro::Entity::update() {
  Log::d("Updating entity <", _id, ">");
}
