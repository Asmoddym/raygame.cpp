#ifndef MACRO_SYSTEMMANAGER_HPP_
# define MACRO_SYSTEMMANAGER_HPP_

# include "Registry.hpp"
#include "System.hpp"

namespace macro {
  class SystemManager {
    std::vector<System *> _systems;

    public:
      SystemManager();
      virtual ~SystemManager();

      void update(Registry &registry);

      template<typename S>
        void set() {
          _systems.emplace_back(new S {});
        }
  };
}

#endif //MACRO_SYSTEMMANAGER_HPP_
