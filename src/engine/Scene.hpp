#ifndef MACRO_SCENE_HPP_
# define MACRO_SCENE_HPP_

# include <string>
#include <unordered_map>
#include "utils/Log.hpp"
#include "Entity.hpp"

namespace macro {
  class Scene {
    private:
      std::string _name;
      std::unordered_map<std::string, Entity> _entities;
      bool _initialized;
  
    public:
      Scene();
      virtual ~Scene();

      void initialize(std::string const &name);
      void destroy();

      void update();

      Entity &createEntity(std::string const &id) {
        if (_entities.find(id) != _entities.end()) {
          throw std::runtime_error(Log::to_s("Entity <", id, "> already exists").c_str());
        }

        _entities.insert(std::make_pair(id, Entity { id }));

        Log::d("[Scene <", _name, ">] Created entity <", id, ">");
        return _entities.at(id);
      }

      std::string const &getName() const { return _name; }
      bool const &initialized() const { return _initialized; }
      std::unordered_map<std::string, Entity> &getEntities() { return _entities; }
  };
}

#endif // MACRO_SCENE_HPP_
