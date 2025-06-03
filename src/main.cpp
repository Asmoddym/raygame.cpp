#include "engine/macro.h"

class Test : public macro::System {
  DefineSystem(Test);

  public:
    inline virtual void update() override {
    }
};

int main() {
  macro::Application app;

  auto background_id = app.generateEntityID();
  app.getRegistry().set<macro::component::Vector2>(background_id, Vector2 { 0, 12 });
  app.getRegistry().set<macro::component::Texture>(background_id, "wabbit_alpha.png");

  // auto a = app.generateEntityID();
  // app.getRegistry().set<macro::component::Vector2>(a, Vector2 { 0, 0 });

  // app.getSystemManager().set<Test>();

  app.run();

  return 0;
}
