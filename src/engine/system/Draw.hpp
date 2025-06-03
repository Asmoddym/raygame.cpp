#ifndef MACRO_SYSTEM_DRAW_HPP_
# define MACRO_SYSTEM_DRAW_HPP_

# include "System.hpp"

namespace macro {
  namespace system {
    class Draw : public System {
      virtual void update(Registry &registry) override;
    };
  }
}

#endif //MACRO_SYSTEM_DRAW_HPP_
