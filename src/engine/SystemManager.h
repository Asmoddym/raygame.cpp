#ifndef MACRO_SYSTEMMANAGER_H_
# define MACRO_SYSTEMMANAGER_H_

# include "Registry.h"
# include "System.h"
# include <memory>

namespace macro {
  class SystemManager {
    Registry &m_registry;
    std::vector<std::unique_ptr<System>> m_systems;

    public:
      inline SystemManager(Registry &r) : m_registry { r } {}
      inline virtual ~SystemManager() {}

      inline void update() {
        for (auto &&system: m_systems) {
          system->performUpdate();
        }
      }

      template<typename S>
        inline void set() {
          static_assert(std::is_base_of<System, S>(), "must be a System");

          m_systems.emplace_back(std::make_unique<S>(m_registry));
        }
  };
}

#endif //MACRO_SYSTEMMANAGER_H_
