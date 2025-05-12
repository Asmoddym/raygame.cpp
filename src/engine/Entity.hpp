#ifndef MACRO_ENTITY_HPP_
# define MACRO_ENTITY_HPP_

# include <vector>
# include <memory>
# include <string>
# include <type_traits>
# include "Component.hpp"
# include "utils/Log.hpp"

namespace macro {
  class Entity {
    private:
      std::string _id;
      std::vector<std::shared_ptr<Component>> _components;

    public:
      Entity(std::string const &id) : _id { id } { Log::d("Constructing entity <", _id, ">"); }
      Entity(Entity const &e) : _id { e._id } { Log::d("Constructing entity <", _id, ">"); }
      virtual ~Entity() { Log::d("Destroying entity <", _id, ">"); }

      void update();

      template<typename C, typename... Args>
        void addComponent(Args &&... args) {
          static_assert(std::is_base_of<Component, C>(), "Not a Component");

          _components.emplace_back(std::make_shared<C>(args...));
        }

      std::string const &getId() const { return _id; }
  };
}

#endif // MACRO_ENTITY_HPP_
