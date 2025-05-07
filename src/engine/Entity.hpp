#ifndef MACRO_ENTITY_HPP_
# define MACRO_ENTITY_HPP_

# include <string>

namespace macro {
  class Entity {
    private:
      std::string const &_id;

    public:
      Entity(std::string const &id) : _id { id } {}
      virtual ~Entity() {}

      void update();

      std::string const &getId() const { return _id; }
  };
}

#endif // MACRO_ENTITY_HPP_
