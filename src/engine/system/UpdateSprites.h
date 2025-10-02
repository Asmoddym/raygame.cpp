#ifndef MACRO_SYSTEM_UPDATESPRITES_H_
# define MACRO_SYSTEM_UPDATESPRITES_H_

# include "System.h"
# include "component/Sprite.h"

namespace macro {
  namespace system {
    class UpdateSprites : public System {
      public:
        DefineSystem(UpdateSprites, 250);

        inline virtual void update() override {
          registry.forEach<component::Sprite>([&](Entity entity) {
              entity.get<component::Sprite>().update();

          });
        }
    };
  }
}

#endif //MACRO_SYSTEM_UPDATESPRITES_H_
