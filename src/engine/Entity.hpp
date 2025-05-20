#ifndef MACRO_ENTITY_HPP_
# define MACRO_ENTITY_HPP_

# include <vector>
# include <memory>
# include <string>
# include <type_traits>
#include "raylib.h"
# include "utils/Log.hpp"
# include "Script.hpp"

namespace macro {
  class Scene;
  class Component;

  class Entity {
    private:
      std::string _id;
      Vector2 _position;

      Scene &_scene;

      std::vector<std::shared_ptr<Component>> _components;
      std::vector<std::shared_ptr<Script>> _scripts;

    public:
      Entity(Scene &scene, std::string const &id) : _scene { scene }, _id { id }, _position { 0, 0 } { Log::d("Constructing entity <", _id, ">"); }
      Entity(Scene &scene, Entity const &e) : _scene { scene }, _id { e._id }, _position { 0, 0 } { Log::d("Constructing entity <", _id, ">"); }

      virtual ~Entity() { Log::d("Destroying entity <", _id, ">"); }

      void update();

      template<typename C, typename... Args>
        void addComponent(Args &&... args) {
          static_assert(std::is_base_of<Component, C>(), "Not a Component");

          _components.emplace_back(std::make_shared<C>(*this, args...));
        }

      template<typename T>
      void addScript() {
        _scripts.emplace_back(std::make_shared<T>());
        _scripts.back().get()->initialize(*this);
      }

      void updateCameraTarget(Vector2 const &t);

      std::string const &getId() const { return _id; }
      Vector2 &getPosition() { return _position; }
  };
}

#endif // MACRO_ENTITY_HPP_
