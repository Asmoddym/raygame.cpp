#include "engine/component/Texture.hpp"
#include "engine/component/Value.hpp"
#include "engine/macro.hpp"

using namespace macro;

class C : public Component {
};

class Test : public macro::System {
  public:
    virtual void update(Registry &registry) override {
      registry.forEach<component::Vector2, component::Texture>(registry.bind(this, &Test::test));
      registry.forEach<component::Vector2>([&](int entity_id) { Log::d("coucou: ", entity_id); });
    }

    void test(Registry &registry, int entity_id) {
        auto &t = registry.get<component::Texture>(entity_id);
        Log::d(">>>> ", t.texture.id);
    }
};

int main() {
  Application app;

  auto background_id = app.generateEntityID();
  app.getRegistry().set<component::Vector2>(background_id, Vector2 { 0, 12 });
  app.getRegistry().set<component::Texture>(background_id, "wabbit_alpha.png");

  auto a = app.generateEntityID();
  app.getRegistry().set<component::Vector2>(a, Vector2 { 0, 0 });

  app.getSystemManager().set<Test>();

  app.run();

  return 0;
}
