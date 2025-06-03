#ifndef MACRO_SYSTEM_DRAW_HPP_
# define MACRO_SYSTEM_DRAW_HPP_

# include "System.hpp"

namespace macro {
  namespace system {
    class Draw : public System {
      DefineSystem(Draw);

      virtual void update() override;
    };
  }
}

#endif //MACRO_SYSTEM_DRAW_HPP_
