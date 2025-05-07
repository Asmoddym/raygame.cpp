#ifndef MACRO_APPLICATION_HPP_
# define MACRO_APPLICATION_HPP_

# include <type_traits>
# include "Scene.hpp"

namespace macro {
  class Application {
    public:
      Application();
      ~Application();

      template<typename T>
      void run() {
        static_assert(std::is_base_of<Scene, T>(), "Not a base of Scene");
      }
  };
}

#endif // MACRO_APPLICATION_HPP_
