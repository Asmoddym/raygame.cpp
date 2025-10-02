#ifndef RG_COMPONENT_POSITION_H_
# define RG_COMPONENT_POSITION_H_

# include "Component.h"

namespace macro {
  namespace component {
    struct Position : public macro::Component {
      int x;
      int y;
    };
  }
}

#endif // !RG_COMPONENT_POSITION_H_
