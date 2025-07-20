#include "engine/macro.h"
#include <algorithm>

namespace rg {
  namespace component {
    struct Controllable : public macro::Component {
      inline Controllable() {}
    };

    struct PhysicsProperties : public macro::component::Value<Vector2> {
      bool movable = false;

      PhysicsProperties(bool mov = false) : macro::component::Value<Vector2> { Vector2 { 0, 0 } }, movable { mov } {}
    };

    struct Velocity : public macro::component::Value<Vector2> {
      inline Velocity(float x = 0, float y = 0) : macro::component::Value<Vector2> { Vector2 { x, y } } {}
      inline Velocity(Vector2 v) : macro::component::Value<Vector2> { v } {}
    };
  }

  namespace system {
    class Move: public macro::System {
      DefineSystem(Move, 16);

    public:
      inline virtual void update() override {
        registry.forEach<component::PhysicsProperties, component::Controllable>(registry.bind(this, &Move::moveControllable));
        registry.forEach<component::PhysicsProperties, component::Velocity>(registry.bind(this, &Move::moveVelocity));
      }

      inline void moveVelocity(macro::Entity entity) {
        auto &r = entity.get<macro::component::Rectangle>().value;
        auto &v = entity.get<component::Velocity>().value;

        r.x += v.x;
        r.y += v.y;
      }

      inline void moveControllable(macro::Entity entity) {
        auto &rect = entity.get<macro::component::Rectangle>().value;

        if (entity.has<component::Controllable>()) {
          if (IsKeyDown(KEY_LEFT)) { rect.x -= 5; }
          if (IsKeyDown(KEY_RIGHT)) { rect.x += 5; }
          if (IsKeyDown(KEY_UP)) { rect.y -= 5; }
          if (IsKeyDown(KEY_DOWN)) { rect.y += 5; }
        }
      }
    };

    class Collision: public macro::System {
      DefineSystem(Collision, 5);

      private:
      bool m_showBounds = false;

      public:
      inline virtual void update() override {
        if (IsKeyPressed(KEY_B)) {
          m_showBounds = !m_showBounds;
        }

        std::vector<EdgeData> xPoints;
        std::vector<int> xActiveIntervals;

        registry.forEach<macro::component::Rectangle, component::PhysicsProperties>([&](macro::Entity e) {
          auto &rect = e.get<macro::component::Rectangle>().value;

          xPoints.emplace_back(EdgeData { e.id, rect.x, 0 });
          xPoints.emplace_back(EdgeData { e.id, rect.x + rect.width, 1 });
        });

        std::sort(xPoints.begin(), xPoints.end(), [&](EdgeData &a, EdgeData &b) { return a.v < b.v; });

        // Sort & sweep implementation from https://leanrada.com/notes/sweep-and-prune/

        for (auto &&x: xPoints) {
          if (x.type == 0) {
            macro::Entity entity = registry.getEntity(x.id);

            for (auto &&other: xActiveIntervals) {
              macro::Entity otherEntity = registry.getEntity(other);

              resolveCollision(entity, otherEntity);
            }

            xActiveIntervals.emplace_back(x.id);
          } else {
            xActiveIntervals.erase(std::find(xActiveIntervals.begin(), xActiveIntervals.end(), x.id));
          }
        }
      }

      private:

      inline void resolveCollision(macro::Entity &entity, macro::Entity &otherEntity) {
        auto &rectangle = entity.get<macro::component::Rectangle>().value;
        auto &otherRectangle = otherEntity.get<macro::component::Rectangle>().value;

        if (!CheckCollisionRecs(rectangle, otherRectangle)) return ;

        auto &collider = entity.get<component::PhysicsProperties>();
        auto &otherCollider = otherEntity.get<component::PhysicsProperties>();

        Vector2 rectangleCenter = calculateCenter(rectangle);
        Vector2 otherRectangleCenter = calculateCenter(otherRectangle);

        Vector2 diff = { rectangleCenter.x - otherRectangleCenter.x, rectangleCenter.y - otherRectangleCenter.y };
        Vector2 normalized = normalize(diff);
        auto collisionRec = GetCollisionRec(rectangle, otherRectangle);

        // TODO: I should be able to remove left and/or right as I know there will be a X collision, and it should always be on the left (I think?)
        float max = 0.0f;
        unsigned int best_match = -1;
        for (unsigned int i = 0; i < 4; i++)
        {
          float dot_product = normalized.x * m_compass[i].x + normalized.y * m_compass[i].y;
          if (dot_product > max)
          {
            max = dot_product;
            best_match = i;
          }
        }

        if (best_match == LEFT || best_match == RIGHT) {
          float midDiff = collisionRec.width / 2;

          // As the algorithm begins with X coord, we know rectangle will always be the entity at the right.
          if (collider.movable) {
            rectangle.x += midDiff;
          }
          if (otherCollider.movable) {
            otherRectangle.x -= midDiff;
          }
        } else {
          float midDiff = collisionRec.height / 2;

          // Here, we need to check in which direction the collision occurred
          midDiff *= best_match == UP ? 1 : -1;

          if (collider.movable) {
            rectangle.y += midDiff;
          }
          if (otherCollider.movable) {
            otherRectangle.y -= midDiff;
          }
        }

        if (m_showBounds) {
          DrawRectangleLinesEx(rectangle, 1, collider.movable ? GREEN : BLUE);
          DrawRectangleLinesEx(otherRectangle, 1, otherCollider.movable ? YELLOW : BLUE);
          DrawRectangleRec(collisionRec, RED);
        }
      }

      inline Vector2 calculateCenter(::Rectangle &rect) {
        Vector2 rectHalfExtents = { rect.width / 2, rect.height / 2 };

        return { rect.x + rectHalfExtents.x, rect.y + rectHalfExtents.y };
      }

      Vector2 normalize(const Vector2 &v) {
        float length_of_v = sqrt((v.x * v.x) + (v.y * v.y));
        return Vector2 { v.x / length_of_v, v.y / length_of_v };
      }

      enum Direction {
        UP,
        RIGHT,
        DOWN,
        LEFT
      };

      static inline Vector2 m_compass[] = {
        { 0, 1 }, // up
        { 1, 0 }, // right
        { 0, -1 }, // down
        { -1, 0 }, // left
      };

      struct EdgeData {
        int id;
        float v;
        int type;
      };
    };
  }
}



struct Map {
  static std::vector<std::string> const lines() {
    return { "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    };
    // return { "0", "°", "a" };
  }

  static void generate(macro::Application &app) {
    int y = 3;
    for (auto &&l: lines()) {
      int x = 3;
      for (auto &&c: l) {
        auto &e = app.generateEntity()
          .set<macro::component::Rectangle>((float)x * 32, (float)y * 32, 32, 32)
          .set<macro::component::Texture>("wabbit_alpha.png")
          .set<rg::component::PhysicsProperties>(true)
          .set<rg::component::Velocity>();

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
    .set<rg::component::PhysicsProperties>(true);

  auto npc = app.generateEntity();
  npc
    .set<macro::component::Rectangle>(400.f, 30.f, 32, 32)
    .set<macro::component::Texture>("wabbit_alpha.png")
    .set<rg::component::PhysicsProperties>(true);

  auto wall = app.generateEntity();
  wall
    .set<macro::component::Rectangle>(600.f, 30.f, 32, 32)
    .set<macro::component::Texture>("wabbit_alpha.png")
    .set<rg::component::PhysicsProperties>(false);

  app.getSystemManager().set<rg::system::Move>();
  app.getSystemManager().set<rg::system::Collision>();

  Map::generate(app);

  app.run();

  return 0;
}
