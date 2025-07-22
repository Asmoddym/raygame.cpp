#ifndef RG_COMPONENTS_H_
# define RG_COMPONENTS_H_

# include "macro.h"
# include "component/Controllable.hpp"

namespace rg {
  namespace component {
    DefineValueComponent(Movable, bool);
    DefineValueComponent(Velocity, Vector2);
  }
}

#endif // !RG_COMPONENTS_H_
