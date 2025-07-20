#ifndef MACRO_COMPONENTMANAGER_H_
# define MACRO_COMPONENTMANAGER_H_

# include <functional>
# include <stdexcept>
# include <type_traits>
# include "Component.h"

namespace macro {
  class Registry {
    public:
  struct Entity {
    int id;
    Registry &registry;

    public:
      inline Entity(Registry &r, int i) : registry { r }, id { i } {}
      inline ~Entity() {}

      template<typename... Cs, typename... Args>
        inline Entity &set(Args&&... args) { registry.set<Cs...>(id, args...); return *this; }

      template<typename C>
        inline C &get() { return registry.get<C>(id); }

      template<typename C>
        inline bool has() { return registry.has<C>(id); }
  };

    private:
      std::vector<Component *> m_components;
      std::unordered_map<int, std::vector<Component *>> m_entities;

    public:
      inline Registry() {}
      inline virtual ~Registry() {
        for (auto &&component: m_components) {
          delete component;
        }
      }

      template<typename C, typename... Args>
        inline Registry &set(int entity_id, Args&&... args) {
          C *c = new C(args...);

          m_components.emplace_back(c);
          m_entities[entity_id].emplace_back(c);

          return *this;
        }

      inline Entity getEntity(int entity_id) {
        return Entity { *this, entity_id };
      }

      template<typename C>
        inline C &get(int entity_id) {
          auto &components = m_entities[entity_id];
          auto it = std::find_if(components.begin(), components.end(), [&](const Component *i) { return dynamic_cast<const C *>(i); });

          if (it == components.end()) {
            throw std::runtime_error("entity has no requested component");
          }

          return *static_cast<C *>(*it);
        }

      template<typename C>
        inline bool has(int entity_id) {
          auto &components = m_entities[entity_id];
          auto it = std::find_if(components.begin(), components.end(), [&](const Component *i) { return dynamic_cast<const C *>(i); });

          return it != components.end();
        }

      template<typename... Cs>
        inline void forEach(std::function<void (Entity)> const &fn) {
          assert_component_list<Cs...>();

          for (auto &&pair: m_entities) {
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
              fn(Entity { *this, pair.first });
            }
          }
        }

      template<typename T, typename U>
        inline std::function<void(Entity)> bind(T *ptr, U const &&fn) {
          return std::bind(fn, ptr, std::placeholders::_1);
        }

      inline std::unordered_map<int, std::vector<Component *>> const &getEntities() const { return m_entities; }

    private:
      template<typename... Cs>
        inline void assert_component_list() {
          static_assert(std::conjunction<std::bool_constant<std::is_base_of_v<Component, Cs>>...>::value, "Not a base of component");
        }
  };

  typedef Registry::Entity Entity;
}

#endif //MACRO_COMPONENTMANAGER_H_
