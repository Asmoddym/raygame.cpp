#include "engine/macro.h"
#include "raylib.h"
#include <algorithm>
#include <cmath>

using namespace macro;

struct MovableComponent : public Component {

  inline MovableComponent() {}
};

struct ColliderComponent : public component::Value<Vector2> {
  bool movable = false;
  Vector2 previousPosition;

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
      auto &previousPosition = entity.get<ColliderComponent>().previousPosition;

      previousPosition.x = rect.x;
      previousPosition.y = rect.y;

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
class CollisionSystem : public System {
  DefineSystem(CollisionSystem);

  bool m_showBounds = false;

  public:
    inline virtual void update() override {
      if (IsKeyPressed(KEY_B)) {
        m_showBounds = !m_showBounds;
      }

      registry.forEach<component::Value<::Rectangle>, ColliderComponent>(registry.bind(this, &CollisionSystem::process));
    }

    inline void process(Entity entity) {
      auto &rectangle = entity.get<component::Value<::Rectangle>>().value;
      auto &previousPosition = entity.get<ColliderComponent>().previousPosition;
      float xDelta = rectangle.x - previousPosition.x;
      float yDelta = rectangle.y - previousPosition.y;
      Vector2 rectangleHalfExtents = { rectangle.width / 2, rectangle.height / 2 };
      Vector2 rectangleCenter = { rectangle.x + rectangleHalfExtents.x, rectangle.y + rectangleHalfExtents.y };

      // if (!entity.get<ColliderComponent>().movable) return ;
      
      bool collisionExisting = true;
      int iterations = 3;

      while (collisionExisting && iterations > 0) {
        iterations--;
        collisionExisting = false;

        registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity otherEntity) {
            if (collisionExisting) { return ; }
            if (otherEntity.id == entity.id) { return; }

            collisionExisting = CheckCollisionRecs(rectangle, otherEntity.get<component::Value<::Rectangle>>().value);
        });

      registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity otherEntity) {
          // We don't want to check entity's properties against itself
          if (otherEntity.id == entity.id) { return; }

          auto &otherRectangle = otherEntity.get<component::Value<::Rectangle>>().value;
          auto &otherCollider = otherEntity.get<ColliderComponent>();

          // if (CheckCollisionRecs(rectangle, otherRectangle)) {
          //   auto collision = GetCollisionRec(rectangle, otherRectangle);

          bool collisionX = rectangle.x + rectangle.width >= otherRectangle.x &&
          otherRectangle.x + otherRectangle.width >= rectangle.x;
          // collision y-axis?
          bool collisionY = rectangle.y + rectangle.height >= otherRectangle.y &&
          otherRectangle.y + otherRectangle.height >= rectangle.y;
          // collision only if on both axes


          Vector2 otherRectangleHalfExtents = { otherRectangle.width / 2, otherRectangle.height / 2 };
          Vector2 otherRectangleCenter = { otherRectangle.x + otherRectangleHalfExtents.x, otherRectangle.y + otherRectangleHalfExtents.y };
          Vector2 diff = { rectangleCenter.x - otherRectangleCenter.x, rectangleCenter.y - otherRectangleCenter.y };

          // if (collisionX && collisionY) {
          if (CheckCollisionRecs(rectangle, otherRectangle)) {
            collisionExisting = true;
            Vector2 normalized = normalize(diff);

            Vector2 compass[] = {
              { 0, 1 }, // up
              { 1, 0 }, // right
              { 0, -1 }, // down
              { -1, 0 }, // left
            };
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
              float velocity = entity.has<Particle>() ? entity.get<Particle>().velocity.x : 3;
              rectangle.x += velocity * (best_match == LEFT ? -1 : 1);
            }

            if (best_match == UP || best_match == DOWN) {
              float velocity = entity.has<Particle>() ? entity.get<Particle>().velocity.y : 3;
              rectangle.y += velocity * (best_match == DOWN ? -1 : 1);
            }
          }
      });




      }


      return;
      }

    //   auto &rectangle = entity.get<component::Value<::Rectangle>>().value;
    //   auto &previousPosition = entity.get<ColliderComponent>().previousPosition;
    //
    //   float xDelta = rectangle.x - previousPosition.x;
    //   float yDelta = rectangle.y - previousPosition.y;
    //
    //   // TODO: collidable components should have their own position and dimensions instead of using Rectangle
    //   registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity otherEntity) {
    //     // We don't want to check entity's properties against itself
    //     if (otherEntity.id == entity.id) { return; }
    //
    //     auto &otherRectangle = otherEntity.get<component::Value<::Rectangle>>().value;
    //     auto newRectangle = rectangle;
    //     auto &otherCollider = otherEntity.get<ColliderComponent>();
    //
    //     auto collision = GetCollisionRec(rectangle, otherRectangle);
    //     // if (entity.id == 0 && (xDelta != 0 || yDelta != 0)) DebugLog(xDelta, ", ", yDelta, ", ", collision.x, ", ", collision.y, ", ", collision.width, ", ", collision.height);
    //
    //     if (m_showBounds) {
    //       DrawRectangleLinesEx(otherRectangle, 1, BLUE);
    //       DrawRectangleLinesEx(collision, 1, YELLOW);
    //     }
    //
    //     // Checking x collisions independently from y collisions, as both could be triggered at the same time.
    //     // If x collision is at fault, y collision would be impacted because both axes would have been moved (and vice-versa).
    //     // For each, if a collision was detected, move to the closest we can get to the edge of the incrimated axis.
    //
    //     if (xDelta != 0 && CheckCollisionRecs({ rectangle.x, previousPosition.y, rectangle.width, rectangle.height }, otherRectangle)) {
    //       const auto collidingLeft = rectangle.x + rectangle.width > otherRectangle.x && rectangle.x < otherRectangle.x;
    //       const auto collidingRight = rectangle.x < otherRectangle.x + otherRectangle.width && rectangle.x > otherRectangle.x;
    //
    //       if (collidingRight || collidingLeft) {
    //         // if (otherCollider.movable) {
    //         //     otherRectangle.x += xDelta;
    //         //
    //         // } else {
    //
    //           // newRectangle.x = otherRectangle.x + (collidingRight ? 1 : -1) * otherRectangle.width;
    //           newRectangle.x = previousPosition.x;
    //           DrawRectangleLinesEx(otherRectangle, 1, RED);
    //         // }
    //       }
    //     }
    //
    //     // FIXME: This system won't work because previously updated entities can be touched, so this will break next iterations.
    //     // Perhaps there should be 2 systems:
    //     // - 1 system to check for collisions and put them in ColliderComponent
    //     // - 1 system to apply these collisions, either until there is no more collision with this particular item, or set the current collision to the next element (may not work if the object collides with multiple items)
    //     // In essence, how to handle multiple collisions at the same time?
    //     if (yDelta != 0 && CheckCollisionRecs({ previousPosition.x, rectangle.y, rectangle.width, rectangle.height }, otherRectangle)) {
    //       auto collidingUp = rectangle.y + rectangle.height > otherRectangle.y && rectangle.y < otherRectangle.y;
    //       auto collidingDown = rectangle.y < otherRectangle.y + otherRectangle.height && rectangle.y > otherRectangle.y;
    //
    //       if (collidingUp || collidingDown) {
    //         // if (otherCollider.movable) {
    //         //   otherRectangle.y += yDelta;
    //         // } else {
    //         // newRectangle.y = otherRectangle.y + (collidingDown ? 1 : -1) * otherRectangle.height;
    //           newRectangle.y = previousPosition.y;
    //           DrawRectangleLinesEx(otherRectangle, 1, RED);
    //         // }
    //       }
    //     }
    //
    //     // previousPosition = { newRectangle.x, newRectangle.y };
    //     rectangle = newRectangle;
    //   });
    //
    //   if (m_showBounds) {
    //     DrawRectangleLinesEx(rectangle, 1, GREEN);
    //   }
    // }
};

struct Map {
  static std::vector<std::string> const lines() {
    return { "000000000", "0000", "0000000" };
  }

  static void generate(Application &app) {
    int y = 10;
    for (auto &&l: lines()) {
      int x = 10;
      for (auto &&c: l) {
        auto &e = app.generateEntity().set<component::Value<::Rectangle>>(::Rectangle { (float)x * 32, (float)y * 32, 32, 32, }).set<component::Texture>("wabbit_alpha.png").set<ColliderComponent>(false).set<Particle>(Vector2 {(float)x * 32, (float)y * 32});


        float rx = (rand() % 100) / 100.f;
        float ry = (rand() % 100) / 100.f;

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

  app.getSystemManager().set<MoveSystem>();
  app.getSystemManager().set<ParticleSystem>();
  app.getSystemManager().set<CollisionSystem>();

  Map::generate(app);

  app.run();

  return 0;
}
