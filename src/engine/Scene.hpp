#ifndef MACRO_SCENE_HPP_
# define MACRO_SCENE_HPP_

#include <algorithm>
#include <iterator>
# include <vector>
#include <unordered_map>
#include "Component.hpp"
#include "raylib.h"

namespace macro {
  class Scene {
    class Entity {
      private:
        int _id;
        Scene &_scene;

      public:
        Entity(int id, Scene &s) : _id { id }, _scene { s } {}
        
        template<typename T, typename... Args>
          T &addComponent(Args&&... args) { return _scene.addComponent<T>(_id, args...); }

        template<typename T>
          T &getComponent() { return _scene.getComponent<T>(_id); }
    };

    private:
      int _entity_count;
      std::vector<Component *> _components;
      std::unordered_map<int, std::vector<Component *>> _components_by_entity;
      Camera2D _camera;
  
    public:
      Scene();
      virtual ~Scene();

      void update();

      Entity createEntity() {
        return Entity { _entity_count++, *this };
      }

      //TODO: Move this into a registry of some sort
      template<typename T>
      static constexpr inline bool componentMatcher(const Component *item) { return dynamic_cast<const T *>(item); }

      template<typename T, typename... Args>
        T &addComponent(int entity_id, Args&&... args) {
          T *c = new T { args... };
          _components.emplace_back(c);
          _components_by_entity[entity_id].emplace_back(c);

          return *c;
        }

      template<typename T>
        T &getComponent(int entity_id) {
          const auto &v = _components_by_entity[entity_id];
          const auto result = std::find_if(v.begin(), v.end(), &componentMatcher<T>);

          return *static_cast<T *>(*result);
        }

      template<typename T>
        void findAndCopyComponentsForType(std::vector<Component *> &matches) {
          std::copy_if(_components.begin(), _components.end(), std::back_inserter(matches), &componentMatcher<T>);
        }

      Camera2D &getCamera() { return _camera; }

    private:
      template<typename... Args>
        std::vector<Component *> getComponentsByType() {
          std::vector<Component *> matches;

          (findAndCopyComponentsForType<Args>(matches), ...);

          return matches;
        }
  };
}

#endif // MACRO_SCENE_HPP_
