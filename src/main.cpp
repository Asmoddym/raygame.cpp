#include "engine/macro.h"

#include "rg/components.h"
#include "rg/systems.h"

struct Map {
  static std::vector<std::string> const lines() {
    return {
      "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
      "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
      "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    };
  }

  static void generate(macro::Application &app) {
    int y = 3;
    for (auto &&l: lines()) {
      int x = 3;
      for (auto &&c: l) {
        auto &e = app.generateEntity()
          .set<macro::component::Rectangle>((float)x * 32, (float)y * 32, 32, 32)
          .set<macro::component::Texture>("wabbit_alpha.png")
          .set<rg::component::Movable>(true)
          .set<rg::component::Velocity>(Vector2 { 0, 0 });

        auto &velocity = e.get<rg::component::Velocity>().value;

        float rx = (rand() % 200) / 100.f;
        float ry = (rand() % 200) / 100.f;

        velocity.x = rx;
        velocity.y = ry;

        if (rand() % 2 == 0) {
          velocity.x *= -1;
        }

        if (rand() % 2 == 0) {
          velocity.y *= -1;
        }

        x++;
      }
      y++;
    }
  }
};

int main() {
  macro::Application app;

  auto player = app.generateEntity();
  player
    //TODO: override this to improve constructor
    // this is used to get the entity's position to draw (maybe should be its own dedicated stuff, PositionComponent + DimensionsComponent for example)
    .set<macro::component::Rectangle>(200.f, 200.f, 32, 32)
    .set<macro::component::Texture>("wabbit_alpha.png")
    .set<rg::component::Controllable>()
    .set<rg::component::Movable>(true);

  auto npc = app.generateEntity();
  npc
    .set<macro::component::Rectangle>(400.f, 30.f, 32, 32)
    .set<macro::component::Texture>("wabbit_alpha.png")
    .set<rg::component::Movable>(true);

  auto wall = app.generateEntity();
  wall
    .set<macro::component::Rectangle>(600.f, 30.f, 32, 32)
    .set<macro::component::Texture>("cursor1.png")
    .set<rg::component::Movable>(false);

  app.getSystemManager().set<rg::system::Move>();
  app.getSystemManager().set<rg::system::Collision>();

  // Must be at the end for timers (for now)
  app.getSystemManager().set<macro::system::Draw>();
  Map::generate(app);

  app.run();

  return 0;
}
