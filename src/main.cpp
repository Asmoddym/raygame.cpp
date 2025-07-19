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

      // if (!entity.get<ColliderComponent>().movable) return ;
      // https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
      
      registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity otherEntity) {
          // We don't want to check entity's properties against itself
          if (otherEntity.id == entity.id) { return; }

          auto &otherRectangle = otherEntity.get<component::Value<::Rectangle>>().value;

          if (CheckCollisionRecs(rectangle, otherRectangle)) {
          Vector2 rectangleHalfExtents = { rectangle.width / 2, rectangle.height / 2 };
          Vector2 rectangleCenter = { rectangle.x + rectangleHalfExtents.x, rectangle.y + rectangleHalfExtents.y };
          auto &otherCollider = otherEntity.get<ColliderComponent>();
          Vector2 otherRectangleHalfExtents = { otherRectangle.width / 2, otherRectangle.height / 2 };
          Vector2 otherRectangleCenter = { otherRectangle.x + otherRectangleHalfExtents.x, otherRectangle.y + otherRectangleHalfExtents.y };
          Vector2 diff = { rectangleCenter.x - otherRectangleCenter.x, rectangleCenter.y - otherRectangleCenter.y };

          Vector2 normalized = normalize(diff);

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

      if (m_showBounds) DrawRectangleLinesEx(rectangle, 1, YELLOW);
      };
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
