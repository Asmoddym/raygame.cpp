#ifndef MACRO_SCENE_HPP_
# define MACRO_SCENE_HPP_

#include <algorithm>
#include <memory>
# include <vector>
#include <unordered_map>
#include "Component.hpp"
#include "raylib.h"

namespace macro {
  class Scene {
    class EntityWrapper {
      private:
        int _id;
        Scene &_scene;

      public:
        EntityWrapper(int id, Scene &s) : _id { id }, _scene { s } {}
        
        template<typename T, typename... Args>
          T &addComponent(Args&&... args) { return _scene.addComponent<T>(_id, args...); }

        template<typename T>
          T &getComponent() { return _scene.getComponent<T>(_id); }
    };

    private:
      int _entity_count;
      std::unordered_map<int, std::vector<std::unique_ptr<Component>>> _components;
      Camera2D _camera;
  
    public:
      Scene();
      virtual ~Scene();

      void update();

      EntityWrapper createEntity() {
        return EntityWrapper { _entity_count++, *this };
      }

      template<typename T, typename... Args>
        T &addComponent(int entity_id, Args&&... args) {
          _components[entity_id].emplace_back(std::make_unique<T>(args...));

          return *static_cast<T *>(_components[entity_id].back().get());
        }

      template<typename T>
        T &getComponent(int entity_id) {
          auto &v = _components[entity_id];

          auto result = std::find_if(v.begin(), v.end(), [&](const std::unique_ptr<Component> &item) { return dynamic_cast<T *>(item.get()); });

          return *static_cast<T *>((*result).get());
        }

      Camera2D &getCamera() { return _camera; }
  };
}

#endif // MACRO_SCENE_HPP_
