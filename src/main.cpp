#include "engine/macro.h"
#include <algorithm>

using namespace macro;

struct MovableComponent : public Component {

  inline MovableComponent() {}
};

struct ColliderComponent : public component::Value<Vector2> {
  bool movable = false;

  ColliderComponent(bool mov = false) : component::Value<Vector2> { Vector2 { 0, 0 } }, movable { mov } {}
};

class MoveSystem : public System {
  DefineSystem(MoveSystem);

  public:
    inline virtual void update() override {
      registry.forEach<ColliderComponent>(registry.bind(this, &MoveSystem::move));
    }

    inline void move(Entity entity) {
      auto &rect = entity.get<component::Value<::Rectangle>>().value;

      if (entity.has<MovableComponent>()) {
        if (IsKeyDown(KEY_LEFT)) { rect.x -= 3; }
        if (IsKeyDown(KEY_RIGHT)) { rect.x += 3; }
        if (IsKeyDown(KEY_UP)) { rect.y -= 3; }
        if (IsKeyDown(KEY_DOWN)) { rect.y += 3; }
      }
    }
};

struct Particle : public Component {
  float mass = 1;
  Vector2 position;
  Vector2 velocity;
  Vector2 appliedForce;

  inline Particle(Vector2 p, Vector2 v = { 0.f, 0.f }) : position { p }, velocity { v}, appliedForce { 0.f, 0.f } {}
};

Vector2 normalize(const Vector2 &v)
{
   float length_of_v = sqrt((v.x * v.x) + (v.y * v.y));
   return Vector2 { v.x / length_of_v, v.y / length_of_v };
}

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};  

Vector2 compass[] = {
  { 0, 1 }, // up
  { 1, 0 }, // right
  { 0, -1 }, // down
  { -1, 0 }, // left
};

struct CollisionPoint {
  int id;
  float v;
  int type;
};

class CollisionSystem : public System {
  DefineSystem(CollisionSystem);

  bool m_showBounds = false;

  public:
    inline virtual void update() override {
      if (IsKeyPressed(KEY_B)) {
        m_showBounds = !m_showBounds;
      }

      std::vector<CollisionPoint> xPoints;
      std::vector<int> xActiveIntervals;

      registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity e) {
        auto &rect = e.get<component::Value<::Rectangle>>();

        xPoints.emplace_back(CollisionPoint { e.id, rect.value.x, 0 });
        xPoints.emplace_back(CollisionPoint { e.id, rect.value.x + rect.value.width, 1 });
      });

      std::sort(xPoints.begin(), xPoints.end(), [&](CollisionPoint &a, CollisionPoint &b) { return a.v < b.v; });

      // Sort & sweep implementation from https://leanrada.com/notes/sweep-and-prune/

      for (auto &&x: xPoints) {
        if (x.type == 0) {
          Entity entity = registry.getEntity(x.id);
          auto &rect = entity.get<component::Value<::Rectangle>>().value;

          for (auto &&other: xActiveIntervals) {
            Entity otherEntity = registry.getEntity(other);
            auto &otherRect = otherEntity.get<component::Value<::Rectangle>>().value;

            if (CheckCollisionRecs(rect, otherRect)) {
              resolveCollision(entity, otherEntity);
            }
          }

          xActiveIntervals.emplace_back(x.id);
        } else {
          xActiveIntervals.erase(std::remove_if(xActiveIntervals.begin(), xActiveIntervals.end(), [&](int id) { return id == x.id; }));
        }
      }
    }

    inline void resolveCollision(Entity &entity, Entity &otherEntity) {
      if (otherEntity.id == entity.id) { return; }

      auto &rectangle = entity.get<component::Value<::Rectangle>>().value;
      auto &collider = entity.get<ColliderComponent>();
      Vector2 rectangleHalfExtents = { rectangle.width / 2, rectangle.height / 2 };
      Vector2 rectangleCenter = { rectangle.x + rectangleHalfExtents.x, rectangle.y + rectangleHalfExtents.y };

      auto &otherRectangle = otherEntity.get<component::Value<::Rectangle>>().value;
      auto &otherCollider = otherEntity.get<ColliderComponent>();
      Vector2 otherRectangleHalfExtents = { otherRectangle.width / 2, otherRectangle.height / 2 };
      Vector2 otherRectangleCenter = { otherRectangle.x + otherRectangleHalfExtents.x, otherRectangle.y + otherRectangleHalfExtents.y };

      Vector2 diff = { rectangleCenter.x - otherRectangleCenter.x, rectangleCenter.y - otherRectangleCenter.y };
      Vector2 normalized = normalize(diff);
      auto collisionRec = GetCollisionRec(rectangle, otherRectangle);

      // TODO: I should be able to remove left and/or right as I know there will be a X collision, and it should always be on the left (I think?)
      float max = 0.0f;
      unsigned int best_match = -1;
      for (unsigned int i = 0; i < 4; i++)
      {
        float dot_product = normalized.x * compass[i].x + normalized.y * compass[i].y;
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
};

struct Map {
  static std::vector<std::string> const lines() {
    return { "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    "00000000000000000000000000000000000", "0000", "0000000", "000000000000000000000", "°1209234°02943°0493", "éràç_ékjfh slkfgjhqs lfgksjh lkjh ", "mcvioqsdjhf lsqkjfgh sdlfkjsdh flsdkhjf sdlfkjsdh flsdkhjf sdlfkjehfglaziuhfg zlkjh ",
    };
    // return { "0", "°", "a" };
  }

  static void generate(Application &app) {
    int y = 10;
    for (auto &&l: lines()) {
      int x = 10;
      for (auto &&c: l) {
        auto &e = app.generateEntity().set<component::Value<::Rectangle>>(::Rectangle { (float)x * 32, (float)y * 32, 32, 32, }).set<component::Texture>("wabbit_alpha.png").set<ColliderComponent>(true).set<Particle>(Vector2 {(float)x * 32, (float)y * 32});

        float rx = (rand() % 200) / 100.f;
        float ry = (rand() % 200) / 100.f;

        e.get<Particle>().velocity.x = rx;
        e.get<Particle>().velocity.y = ry;

        if (rand() % 2 == 0) {
          e.get<Particle>().velocity.x *= -1;
        }

        if (rand() % 2 == 0) {
          e.get<Particle>().velocity.y *= -1;
        }

        x++;
      }
      y++;
    }
  }
};

class ParticleSystem : public System {
  DefineSystem(ParticleSystem);

  inline void update() override {
    //TODO: Implement an actual timer
    static int tick = 0;
    tick++;
    if (tick % 2 == 0) return ;

    registry.forEach<Particle>([&](Entity e) {
      auto &p = e.get<Particle>();
      // auto &previousPosition = e.get<ColliderComponent>().previousPosition;
      // auto &force = p.appliedForce;
      //
      // Vector2 acceleration = { force.x / p.mass, force.y / p.mass };
      //
      // p.velocity.x = p.velocity.x + acceleration.x * step;
      // p.velocity.y = p.velocity.y + acceleration.y * step;
      //
      // p.position.x = previousPosition.x + p.velocity.x * step;
      // p.position.y = previousPosition.y + p.velocity.y * step;
      //
      // e.get<component::Value<::Rectangle>>().value.x = p.position.x;
      // e.get<component::Value<::Rectangle>>().value.y = p.position.y;
      //
      // force.x = 0;
      // force.y = 0;
      e.get<component::Value<::Rectangle>>().value.x += p.velocity.x;
      e.get<component::Value<::Rectangle>>().value.y += p.velocity.y;
    });
  }
};

int main() {
  Application app;

  auto player = app.generateEntity();
  player
    //TODO: override this to improve constructor
    // this is used to get the entity's position to draw (maybe should be its own dedicated stuff, PositionComponent + DimensionsComponent for example)
    .set<component::Value<::Rectangle>>(::Rectangle { 200, 200, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<MovableComponent>()
    .set<ColliderComponent>(true);

  auto npc = app.generateEntity();
  npc
    .set<component::Value<::Rectangle>>(::Rectangle { 400, 30, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>(true);

  auto wall = app.generateEntity();
  wall
    .set<component::Value<::Rectangle>>(::Rectangle { 600, 30, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>(false);

  app.getSystemManager().set<MoveSystem>();
  app.getSystemManager().set<ParticleSystem>();
  app.getSystemManager().set<CollisionSystem>();

  Map::generate(app);

  app.run();

  return 0;
}
