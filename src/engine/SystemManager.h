#ifndef MACRO_SYSTEMMANAGER_H_
# define MACRO_SYSTEMMANAGER_H_

# include "Registry.h"
# include "System.h"
# include <memory>

namespace macro {
  class SystemManager {
    Registry &_registry;
    std::vector<std::unique_ptr<System>> _systems;

    public:
      inline SystemManager(Registry &r) : _registry { r } {}
      inline virtual ~SystemManager() {}

      inline void update() {
        for (auto &&system: _systems) {
          system->update();
        }
      }

      template<typename S>
        inline void set() {
          static_assert(std::is_base_of<System, S>(), "must be a System");

          _systems.emplace_back(std::make_unique<S>(_registry));
        }
  };
}

#endif //MACRO_SYSTEMMANAGER_H_
