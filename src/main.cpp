#include "engine/macro.h"

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
      registry.forEach<MovableComponent>(registry.bind(this, &MoveSystem::move));
    }

    inline void move(Entity entity) {
      auto &rect = entity.get<component::Value<::Rectangle>>().value;
      auto &previousPosition = entity.get<ColliderComponent>().previousPosition;

      previousPosition.x = rect.x;
      previousPosition.y = rect.y;

      if (IsKeyDown(KEY_LEFT)) { rect.x -= 3; }
      if (IsKeyDown(KEY_RIGHT)) { rect.x += 3; }
      if (IsKeyDown(KEY_UP)) { rect.y -= 3; }
      if (IsKeyDown(KEY_DOWN)) { rect.y += 3; }
    }
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

      int xDelta = rectangle.x - previousPosition.x;
      int yDelta = rectangle.y - previousPosition.y;

      // TODO: collidable components should have their own position and dimensions instead of using Rectangle
      registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity otherEntity) {
        // We don't want to check entity's properties against itself
        if (otherEntity.id == entity.id) { return; }

        auto &otherRectangle = otherEntity.get<component::Value<::Rectangle>>().value;
        auto newRectangle = rectangle;
        auto &otherCollider = otherEntity.get<ColliderComponent>();

        if (m_showBounds) {
          auto collision = GetCollisionRec(otherRectangle, rectangle);

          DrawRectangleLinesEx(otherRectangle, 1, BLUE);
          DrawRectangleLinesEx(collision, 1, YELLOW);
        }

        // Checking x collisions independently from y collisions, as both could be triggered at the same time.
        // If x collision is at fault, y collision would be impacted because both axes would have been moved (and vice-versa).
        // For each, if a collision was detected, move to the closest we can get to the edge of the incrimated axis.

        if (xDelta != 0 && CheckCollisionRecs({ rectangle.x, previousPosition.y, rectangle.width, rectangle.height }, otherRectangle)) {
          const auto collidingLeft = rectangle.x + rectangle.width > otherRectangle.x && rectangle.x < otherRectangle.x;
          const auto collidingRight = rectangle.x < otherRectangle.x + otherRectangle.width && rectangle.x > otherRectangle.x;

          if (collidingRight || collidingLeft) {
            // if (otherCollider.movable) {
            //     otherRectangle.x += xDelta;
            // } else {
              newRectangle.x = otherRectangle.x + (collidingRight ? 1 : -1) * otherRectangle.width;
            // }
          }
        }

        // FIXME: This system won't work because previously updated entities can be touched, so this will break next iterations.
        // Perhaps there should be 2 systems:
        // - 1 system to check for collisions and put them in ColliderComponent
        // - 1 system to apply these collisions, either until there is no more collision with this particular item, or set the current collision to the next element (may not work if the object collides with multiple items)
        // In essence, how to handle multiple collisions at the same time?
        if (yDelta != 0 && CheckCollisionRecs({ previousPosition.x, rectangle.y, rectangle.width, rectangle.height }, otherRectangle)) {
          auto collidingUp = rectangle.y + rectangle.height > otherRectangle.y && rectangle.y < otherRectangle.y;
          auto collidingDown = rectangle.y < otherRectangle.y + otherRectangle.height && rectangle.y > otherRectangle.y;

          if (collidingUp || collidingDown) {
            // if (otherCollider.movable) {
            //   otherRectangle.y += yDelta;
            // } else {
            newRectangle.y = otherRectangle.y + (collidingDown ? 1 : -1) * otherRectangle.height;
            // }
          }
        }

        // previousPosition = { rectangle.x, rectangle.y };
        rectangle = newRectangle;
      });

      if (m_showBounds) {
        DrawRectangleLinesEx(rectangle, 1, GREEN);
      }
    }
};

struct Particle : public Component {
  float mass = 1;
  Vector2 position;
  Vector2 velocity;
  Vector2 appliedForce;

  inline Particle(Vector2 p) : position { p }, velocity { 0.f, 0.f }, appliedForce { 0.f, 0.f } {}
};

struct Map {
  static std::vector<std::string> const lines() {
    return { "000000000", "0000", "0000000" };
  }

  static void generate(Application &app) {
    int y = 0;
    for (auto &&l: lines()) {
      int x = 0;
      for (auto &&c: l) {
        app.generateEntity().set<component::Value<::Rectangle>>(::Rectangle { (float)x * 32, (float)y * 32, 32, 32, }).set<component::Texture>("wabbit_alpha.png").set<ColliderComponent>(true).set<Particle>(Vector2 {(float)x * 32, (float)y * 32});

        x++;
      }
      y++;
    }
  }
};

class ParticleSystem : public System {
  DefineSystem(ParticleSystem);

  inline void update() override {
    static float step = 0.05;
    static float total = 0;

    registry.forEach<Particle>([&](Entity e) {
      auto &p = e.get<Particle>();
      auto &force = p.appliedForce;

      // Vector2 force = { total == 0 ? 2000 : (p.velocity.x < 0.01 ? 0 : -8.f), p.mass * 9.81f };
      Vector2 acceleration = { force.x / p.mass, force.y / p.mass };

      p.velocity.x = p.velocity.x + acceleration.x * step;
      p.velocity.y = p.velocity.y + acceleration.y * step;

      p.position.x = p.position.x + p.velocity.x * step;
      p.position.y = p.position.y + p.velocity.y * step;

      e.get<component::Value<::Rectangle>>().value.x = p.position.x;
      e.get<component::Value<::Rectangle>>().value.y = p.position.y;
    });

    total += step;
  }
};

int main() {
  Application app;

  app.getSystemManager().set<ParticleSystem>();

  auto player = app.generateEntity();
  player
    //TODO: override this to improve constructor
    // this is used to get the entity's position to draw (maybe should be its own dedicated stuff, PositionComponent + DimensionsComponent for example)
    .set<component::Value<::Rectangle>>(::Rectangle { 200, 200, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<MovableComponent>()
    .set<ColliderComponent>(false);

  auto npc = app.generateEntity();
  npc
    .set<component::Value<::Rectangle>>(::Rectangle { -100, 30, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>(true);

  app.getSystemManager().set<MoveSystem>();
  app.getSystemManager().set<CollisionSystem>();

  Map::generate(app);

  app.run();

  return 0;
}
