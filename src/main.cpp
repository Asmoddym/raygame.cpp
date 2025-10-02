#include "engine/macro.h"

#include "rg/components.h"
#include "rg/systems.h"
#include "rg/enum/Direction.h"

int main() {
  macro::Application app;

  auto player = app.generateEntity();
  player
    // Width and height will be used to draw the sprite
    .set<macro::component::Rectangle>(200.f, 200.f, 64, 64)
    .set<macro::component::Sprite, std::unordered_map<int, std::string>>({
        {rg::e_Direction::NONE, "idle.png"},
        {rg::e_Direction::UP, "up.png"},
        {rg::e_Direction::DOWN, "down.png"},
        {rg::e_Direction::LEFT, "left.png"},
        {rg::e_Direction::RIGHT, "right.png"},
        })
    .set<rg::component::Controllable>()
    .set<rg::component::Movable>(true);

  auto npc = app.generateEntity();
  npc
    .set<macro::component::Rectangle>(400.f, 30.f, 32, 32)
    .set<macro::component::Texture>("wabbit_alpha.png")
    .set<rg::component::Movable>(false);

  app.getSystemManager().set<rg::system::Move>();
  app.getSystemManager().set<rg::system::Collision>();
  // Must be at the end for timers (for now)
  app.getSystemManager().set<macro::system::Draw>();

  app.run();

  return 0;
}
