#ifndef MACRO_APPLICATION_HPP_
# define MACRO_APPLICATION_HPP_

# include "Scene.hpp"
#include "raylib.h"

namespace macro {
  class Application {
    private:
      Scene _scene;

    public:
      Application();
      ~Application();

      void run();

      Scene &initializeScene(std::string const &name) {
        if (_scene.initialized()) {
          _scene.destroy();
        }

        _scene.initialize(name);

        return _scene;
      }
  };
}

#endif // MACRO_APPLICATION_HPP_
