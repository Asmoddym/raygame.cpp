#ifndef APPLICATION_HPP_
# define APPLICATION_HPP_

# include <type_traits>
# include "Scene.hpp"

class Application {
  public:
    Application();
    ~Application();

    template<typename T>
    void run() {
      static_assert(std::is_base_of<Scene, T>(), "Not a base of Scene");
    }
};

#endif // APPLICATION_HPP_
