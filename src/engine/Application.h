#ifndef MACRO_APPLICATION_H_
# define MACRO_APPLICATION_H_

# include "raylib.h"
# include "Registry.h"
# include "Entity.h"
# include "SystemManager.h"

namespace macro {
  class Application {
    private:
      Registry _registry;
      SystemManager _system_manager { _registry };

      int _entity_count = 0;
      Camera2D _camera = { 0 };

    public:
      Application();
      inline ~Application() {}

      void run();

      inline Entity generateEntity() { return Entity { _registry, _entity_count++ }; }

      // Getters

      inline Registry &getRegistry() { return _registry; }
      inline SystemManager &getSystemManager() { return _system_manager; }
  };
}

#endif // MACRO_APPLICATION_H_
