#ifndef MACRO_SCENEMANAGER_HPP_
# define MACRO_SCENEMANAGER_HPP_

#include <memory>
#include <vector>
#include "Scene.hpp"

namespace macro {
  class SceneManager {
    private:
      std::vector<std::unique_ptr<Scene>> _scenes;

    public:
      SceneManager() {}
      virtual ~SceneManager() {}

      template<typename T>
      void create() {
        static_assert(std::is_base_of<Scene, T>(), "Not a base of Scene");

        _scenes.emplace_back(std::make_unique<T>());
      }
  };
}

#endif // MACRO_SCENEMANAGER_HPP_
