#ifndef MACRO_APPLICATION_H_
# define MACRO_APPLICATION_H_

# include "raylib.h"
# include "Registry.h"
# include "SystemManager.h"

namespace macro {
  class Application {
    private:
      Camera2D _camera;

      int _entity_count;
      Registry _registry;
      SystemManager _system_manager;

    public:
      Application();
      inline ~Application() {}

      void run();

      inline int generateEntityID() { return _entity_count++; }

      // Getters

      inline Registry &getRegistry() { return _registry; }
      inline SystemManager &getSystemManager() { return _system_manager; }
  };
}

#endif // MACRO_APPLICATION_H_
