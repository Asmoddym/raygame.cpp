
#ifndef MACRO_SCRIPT_HPP_
# define MACRO_SCRIPT_HPP_

namespace macro {
  class Entity;

  class Script {
    public:
      virtual void initialize(Entity &e) = 0;
      virtual void update(Entity &e) = 0;
  };
}

#endif // MACRO_SCRIPT_HPP_
