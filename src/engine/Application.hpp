#ifndef MACRO_APPLICATION_HPP_
# define MACRO_APPLICATION_HPP_

# include "SceneManager.hpp"

namespace macro {
  class Application {
    private:
      SceneManager _scene_manager;

    public:
      Application();
      ~Application();

      void run();

      template<typename T>
        void registerMainScene() {
          auto scene_ptr = _scene_manager.create<T>();

          _scene_manager.setCurrentScene(scene_ptr);
        }

      SceneManager &getSceneManager() { return _scene_manager; }
  };
}

#endif // MACRO_APPLICATION_HPP_
