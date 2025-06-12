#ifndef MACRO_SYSTEM_DRAW_H_
# define MACRO_SYSTEM_DRAW_H_

# include "System.h"

namespace macro {
  namespace system {
    class Draw : public System {
      DefineSystem(Draw);

      virtual void update() override;
    };
  }
}

#endif //MACRO_SYSTEM_DRAW_H_
