#ifndef MACRO_APPLICATION_H_
# define MACRO_APPLICATION_H_

# include "raylib.h"
# include "Registry.h"
# include "SystemManager.h"

namespace macro {
  class Application {
    private:
      Registry m_registry;
      SystemManager m_systemManager { m_registry };

      int m_entityCount = 0;
      Camera2D m_camera = { 0 };

    public:
      Application();
      inline ~Application() {}

      void run();

      inline Entity generateEntity() { return Entity { m_registry, m_entityCount++ }; }

      // Getters

      inline Registry &getRegistry() { return m_registry; }
      inline SystemManager &getSystemManager() { return m_systemManager; }
  };
}

#endif // MACRO_APPLICATION_H_
