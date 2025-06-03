#include "engine/macro.hpp"

class Test : public macro::System {
  public:
    virtual void update(macro::Registry &registry) override {
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
