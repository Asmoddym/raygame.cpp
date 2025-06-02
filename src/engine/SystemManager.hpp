#ifndef MACRO_SYSTEMMANAGER_HPP_
# define MACRO_SYSTEMMANAGER_HPP_

# include "Registry.hpp"

namespace macro {
  class System {
    public:
      virtual void update(Registry &registry) = 0;
  };
}

namespace macro {
  class SystemManager {
    std::vector<System *> _systems;

    public:
    void update(Registry &registry);

    template<typename S>
      void set() {
        _systems.emplace_back(new S {});
      }
  };
}

#endif //MACRO_SYSTEMMANAGER_HPP_
