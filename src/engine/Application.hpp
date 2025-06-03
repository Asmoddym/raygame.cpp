#ifndef MACRO_APPLICATION_HPP_
# define MACRO_APPLICATION_HPP_

# include "Registry.hpp"
# include "SystemManager.hpp"
# include "raylib.h"

namespace macro {
  class Application {
    private:
      Camera2D _camera;

      int _entity_count;
      Registry _registry;
      SystemManager _system_manager;

    public:
      Application();
      ~Application();

      void run();

      Registry &getRegistry() { return _registry; }
      SystemManager &getSystemManager() { return _system_manager; }

      int generateEntityID();
  };
}

#endif // MACRO_APPLICATION_HPP_
