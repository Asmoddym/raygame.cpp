#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <string>

class Scene {
  private:
    std::string const _name;

  public:
    Scene(std::string const &name);
    virtual ~Scene();

    std::string const &getName() const { return _name; }
};

#endif // SCENE_HPP_
