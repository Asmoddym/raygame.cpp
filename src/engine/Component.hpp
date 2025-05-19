#ifndef MACRO_COMPONENT_HPP_
# define MACRO_COMPONENT_HPP_

namespace macro {
  class Entity;

  class Component {
    protected:
      Entity &_entity;

    public:
      Component(Entity &e) : _entity { e } {}
      virtual ~Component() {}

      virtual void update() = 0;
  };
}

#endif // MACRO_COMPONENT_HPP_
