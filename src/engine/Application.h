#ifndef MACRO_APPLICATION_H_
# define MACRO_APPLICATION_H_

#include "network/Client.h"
# include "raylib.h"
# include "Registry.h"
# include "SystemManager.h"
# include "network/Server.h"

namespace macro {
  class Application {
    private:
      Registry m_registry;
      SystemManager m_systemManager { m_registry };
      network::Server m_server;
      network::Client m_client;

      int m_entityCount = 0;
      Camera2D m_camera = { 0 };

    public:
      Application();
      inline ~Application() {}

      void run(bool server);

      inline Entity generateEntity() { return Entity { m_registry, m_entityCount++ }; }

      // Getters

      inline Registry &getRegistry() { return m_registry; }
      inline SystemManager &getSystemManager() { return m_systemManager; }
  };
}

#endif // MACRO_APPLICATION_H_
