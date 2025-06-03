#ifndef MACRO_SYSTEMMANAGER_HPP_
# define MACRO_SYSTEMMANAGER_HPP_

# include "Registry.hpp"
# include "System.hpp"
#include <type_traits>

namespace macro {
  class SystemManager {
    Registry &_registry;
    std::vector<System *> _systems;

    public:
      SystemManager(Registry &registry);
      virtual ~SystemManager();

      void update();

      template<typename S>
        void set() {
          static_assert(std::is_base_of<System, S>(), "must be a System");

          _systems.emplace_back(new S { _registry });
        }
  };
}

#endif //MACRO_SYSTEMMANAGER_HPP_
