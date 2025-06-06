#ifndef MACRO_COMPONENTMANAGER_H_
# define MACRO_COMPONENTMANAGER_H_

# include <functional>
# include <stdexcept>
# include <type_traits>
# include "Component.h"

namespace macro {
  class Registry {
    private:
      std::vector<Component *> _components;
      std::unordered_map<int, std::vector<Component *>> _entities;

    public:
      inline Registry() {}
      inline virtual ~Registry() {
        for (auto &&component: _components) {
          delete component;
        }
      }

      template<typename C, typename... Args>
        inline Registry &set(int entity_id, Args&&... args) {
          C *c = new C(args...);

          _components.emplace_back(c);
          _entities[entity_id].emplace_back(c);

          return *this;
        }

      template<typename C>
        inline C &get(int entity_id) {
          auto &components = _entities[entity_id];
          auto it = std::find_if(components.begin(), components.end(), [&](const Component *i) { return dynamic_cast<const C *>(i); });

          if (it == components.end()) {
            throw std::runtime_error("entity has no requested component");
          }

          return *static_cast<C *>(*it);
        }

      template<typename C>
        inline bool has(int entity_id) {
          auto &components = _entities[entity_id];
          auto it = std::find_if(components.begin(), components.end(), [&](const Component *i) { return dynamic_cast<const C *>(i); });

          return it != components.end();
        }

      template<typename... Cs>
        inline void forEach(std::function<void (Registry &, int)> const &fn) {
          assert_component_list<Cs...>();

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
              fn(*this, pair.first);
            }
          }
        }

      template<typename... Cs>
        inline void forEach(std::function<void(int)> const &fn) {
          forEach<Cs...>([&](Registry &, int entity_id) { fn(entity_id); }); 
        }

      template<typename T, typename U>
        inline std::function<void(int)> bind(T *ptr, U const &&fn) {
          return std::bind(fn, ptr, std::placeholders::_1);
        }

    private:
      template<typename... Cs>
        inline void assert_component_list() {
          static_assert(std::conjunction<std::bool_constant<std::is_base_of_v<Component, Cs>>...>::value, "Not a base of component");
        }
  };
}

#endif //MACRO_COMPONENTMANAGER_H_
