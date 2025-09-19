#ifndef MACRO_SYSTEM_DRAW_H_
# define MACRO_SYSTEM_DRAW_H_

# include "System.h"
# include "raylib.h"
# include "component/Camera.h"

namespace macro {
  namespace system {
    class Draw : public System {
      private:
        Camera2D &m_camera;

      public:
        DefineSystemWithAdditionalInitializes(Draw, UPDATE_EACH_FRAME, m_camera { registry.get<component::Camera>(0).camera });

        virtual void update() override;
    };
  }
}

#endif //MACRO_SYSTEM_DRAW_H_
