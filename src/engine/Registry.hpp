#ifndef MACRO_COMPONENTMANAGER_HPP_
# define MACRO_COMPONENTMANAGER_HPP_

# include <functional>
# include <vector>
# include <unordered_map>
# include "Component.hpp"

namespace macro {
  class Registry {
    public:
    typedef std::vector<Component *> ComponentContainer;
    typedef std::unordered_map<int, ComponentContainer> EntityContainer;

    private:
    ComponentContainer _components;
    EntityContainer _entities;

    public:

    virtual ~Registry();

    ComponentContainer &getForEntityID(int entity_id) {
      return _entities[entity_id];
    }

    EntityContainer &getEntities() { return _entities; }

    template<typename C, typename... Args>
      C *set(int entity_id, Args&&... args) {
        C *c = new C(args...);

        _components.emplace_back(c);
        _entities[entity_id].emplace_back(c);

        return c;
      }

    template<typename C>
      C &get(int entity_id) {
        auto &components = _entities[entity_id];
        auto &it = std::find_if(components.begin(), components.end(), [&](const Component *i) { return dynamic_cast<const C *>(i); });

        return *static_cast<C *>(*it);
     }

    template<typename... Cs>
      void forEach(std::function<void (int)> const &fn) {
        for (auto &&pair: _entities) {
          int matches = 0;

          ([&]() {
            for (auto &component: pair.second) {
              Cs *c = dynamic_cast<Cs *>(component);

              if (!!c) {
                matches++;
                return;
              }
            }
          }(), ...);

          if (matches == sizeof...(Cs)) {
            fn(pair.first);
          }
        }
      }
  };
}

#endif //MACRO_COMPONENTMANAGER_HPP_
