#ifndef MACRO_SCENE_HPP_
# define MACRO_SCENE_HPP_

#include <exception>
# include <string>
#include <unordered_map>
#include "utils/Log.hpp"
#include "Entity.hpp"

namespace macro {
  class Scene {
    private:
      std::string const _name;
      std::unordered_map<std::string, Entity> _entities;
  
    public:
      Scene(std::string const &name);
      virtual ~Scene();

      virtual void initialize() = 0;

      void update();

      Entity &createEntity(std::string const &id) {
        if (_entities.find(id) != _entities.end()) {
          throw std::exception(Log::to_s("Entity <", id, "> already exists").c_str());
        }

        _entities.insert(std::make_pair(id, Entity { id }));

        return _entities.at(id);
      }

      std::string const &getName() const { return _name; }
  };
}

#endif // MACRO_SCENE_HPP_
