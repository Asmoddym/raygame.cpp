#ifndef MACRO_SCENE_HPP_
# define MACRO_SCENE_HPP_

# include <string>

namespace macro {
  class Scene {
    private:
      std::string const _name;
  
    public:
      Scene(std::string const &name);
      virtual ~Scene();
  
      std::string const &getName() const { return _name; }
  };
}

#endif // MACRO_SCENE_HPP_
