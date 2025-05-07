#ifndef MACRO_SCENEMANAGER_HPP_
# define MACRO_SCENEMANAGER_HPP_

#include <memory>
#include <vector>
#include "Scene.hpp"

namespace macro {
  class SceneManager {
    private:
      std::vector<std::shared_ptr<Scene>> _scenes;
      std::shared_ptr<Scene> _current_scene;

    public:
      SceneManager() {}
      virtual ~SceneManager() {}

      void setCurrentScene(std::shared_ptr<Scene> ptr) { _current_scene = ptr; }

      std::shared_ptr<Scene> &getCurrentScene() { return _current_scene; }
      std::vector<std::shared_ptr<Scene>> &getScenes() { return _scenes; }

      template<typename T>
      std::shared_ptr<Scene> &create() {
        static_assert(std::is_base_of<Scene, T>(), "Not a base of Scene");

        _scenes.emplace(_scenes.begin(), std::make_shared<T>());

        return *_scenes.begin();
      }
  };
}

#endif // MACRO_SCENEMANAGER_HPP_
