#ifndef MACRO_SYSTEM_H_
# define MACRO_SYSTEM_H_

# include "Registry.h"

# define DefineSystem(Name) public: \
  inline Name(::macro::Registry &r) : System { r } {} \
  private:

namespace macro {
  class System {
    protected:
      Registry &registry;

    public:
      inline System(Registry &r) : registry { r } {}
      inline virtual ~System() {}

      virtual void update() = 0;
  };
}

#endif //MACRO_SYSTEM_H_
