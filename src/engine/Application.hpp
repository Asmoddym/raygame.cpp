#ifndef MACRO_APPLICATION_HPP_
# define MACRO_APPLICATION_HPP_

# include "Scene.hpp"

namespace macro {
  class Application {
    private:
      Scene _scene;

    public:
      Application();
      ~Application();

      void run();

      Scene &getScene() { return _scene; }
  };
}

#endif // MACRO_APPLICATION_HPP_
