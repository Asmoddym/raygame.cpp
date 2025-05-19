#ifndef MACRO_COMPONENT_CONTROLLABLE_HPP_
# define MACRO_COMPONENT_CONTROLLABLE_HPP_

#include "Component.hpp"
#include "raylib.h"
#include <functional>
#include <utility>
#include <vector>

namespace macro {
  namespace component {
    class Controllable : public Component {
      private:
        std::vector<std::pair<int, std::function<void(Entity &)>>> _pressed_key_triggers;

      public:
        Controllable(Entity &e);
        virtual ~Controllable() override;

        virtual void update() override;

        void onKeyPressed(int k, std::function<void(Entity &)> const &&fn);
    };
  }
}

#endif // MACRO_COMPONENT_CONTROLLABLE_HPP_
