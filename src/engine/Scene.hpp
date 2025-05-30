#ifndef MACRO_SCENE_HPP_
# define MACRO_SCENE_HPP_

#include <algorithm>
#include <memory>
# include <string>
#include <unordered_map>
#include "Component.hpp"
#include "raylib.h"

namespace macro {
  class Scene {
    private:
      std::string _name;
      bool _initialized;
      std::unordered_map<int, std::vector<std::unique_ptr<Component>>> _components;
      Camera2D _camera;
  
    public:
      Scene();
      virtual ~Scene();

      void initialize(std::string const &name);
      void destroy();
      
      void update();

      int createEntity() {
        static int count = 0;

        return count++;
      }

      template<typename T, typename... Args>
        T &addComponent(int entity_id, Args&&... args) {
          _components[entity_id].emplace_back(std::make_unique<T>(args...));

          return *static_cast<T *>(_components[entity_id].back().get());
        }

      template<typename T>
        T &getComponent(int entity_id) {
          auto &v = _components[entity_id];

          auto &result = std::find_if(v.begin(), v.end(), [&](const std::unique_ptr<Component> &item) { return dynamic_cast<T *>(item.get()); });

          return *static_cast<T *>((*result).get());
        }

      std::string const &getName() const { return _name; }
      bool const &initialized() const { return _initialized; }
      Camera2D const &getCamera() const { return _camera; }
      Camera2D &getCamera() { return _camera; }
  };
}

#endif // MACRO_SCENE_HPP_
