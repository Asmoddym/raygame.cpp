#ifndef MACRO_SYSTEM_H_
# define MACRO_SYSTEM_H_

# include "Registry.h"
# include "raylib.h"

# define UPDATE_EACH_FRAME -1
# define DefineSystem(Name, UpdateSpan) public: \
  inline Name(::macro::Registry &r, double u = -1) : System { r, UpdateSpan } {} \
  private:

# define DefineSystemWithAdditionalInitializes(Name, UpdateSpan, BLOCK) public: \
  inline Name(::macro::Registry &r, double u = -1) : System { r, UpdateSpan }, BLOCK {} \
  private:

namespace macro {
  class System {
    private:
      double m_lastUpdateTime = 0;
      double m_updateSpanMilliseconds = -1;

    protected:
      Registry &registry;

    public:
      inline System(Registry &r, double updateSpan) : registry { r }, m_updateSpanMilliseconds { updateSpan } {}
      inline virtual ~System() {}

      virtual void update() = 0;

      inline void performUpdate() {
        if (m_updateSpanMilliseconds == -1) {
          update();
          return;
        }

        double currentTime = GetTime() * 1000;

        if (currentTime - m_lastUpdateTime > m_updateSpanMilliseconds) {
          update();
          m_lastUpdateTime = currentTime;
        }
      }
  };
}

#endif //MACRO_SYSTEM_H_
