#ifndef RG_COMPONENTS_H_
# define RG_COMPONENTS_H_

# include "macro.h"
# include "component/Controllable.h"

namespace rg {
  namespace component {
    DefineValueComponent(Movable, bool);
    DefineValueComponent(Velocity, Vector2);
  }
}

#endif // !RG_COMPONENTS_H_
