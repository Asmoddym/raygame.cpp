#ifndef MACRO_APPLICATION_HPP_
# define MACRO_APPLICATION_HPP_

# include "utils/Log.hpp"
# include "SceneManager.hpp"
# include "InputManager.hpp"

namespace macro {
  class Application {
    private:
      SceneManager _scene_manager;
      InputManager _input_manager;

    public:
      Application();
      ~Application();

      template<typename T>
        void registerMainScene() {
          _scene_manager.create<T>();
        }

      void run() {
        Log::d("Running!");
      }
  };
}

#endif // MACRO_APPLICATION_HPP_
