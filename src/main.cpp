#include "engine/macro.h"

using namespace macro;

struct MovableComponent : public Component {
  Vector2 previousPosition;

  inline MovableComponent(Vector2 v) : previousPosition { v } {}
};

struct ColliderComponent : public component::Value<Vector2> {
  bool movable = false;

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
      auto &previousPosition = entity.get<MovableComponent>().previousPosition;

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

      registry.forEach<component::Value<::Rectangle>, MovableComponent>(registry.bind(this, &CollisionSystem::process));
    }

    inline void process(Entity entity) {
      auto &rectangle = entity.get<component::Value<::Rectangle>>().value;
      auto &previousPosition = entity.get<MovableComponent>().previousPosition;

      bool xMoved = rectangle.x != previousPosition.x;
      bool yMoved = rectangle.y != previousPosition.y;

      // TODO: collidable components should have their own position and dimensions instead of using Rectangle
      registry.forEach<component::Value<::Rectangle>, ColliderComponent>([&](Entity otherEntity) {
        // We don't want to check entity's properties against itself
        if (otherEntity.id == entity.id) { return; }

        auto &otherRectangle = otherEntity.get<component::Value<::Rectangle>>().value;
        auto newRectangle = rectangle;

        if (m_showBounds) {
          auto collision = GetCollisionRec(otherRectangle, rectangle);

          DrawRectangleLinesEx(otherRectangle, 1, BLUE);
          DrawRectangleLinesEx(collision, 1, YELLOW);
        }

        // Checking x collisions independently from y collisions, as both could be triggered at the same time.
        // If x collision is at fault, y collision would be impacted because both axes would have been moved (and vice-versa).
        // For each, if a collision was detected, move to the closest we can get to the edge of the incrimated axis.

        if (xMoved && CheckCollisionRecs({ rectangle.x, previousPosition.y, rectangle.width, rectangle.height }, otherRectangle)) {
          const auto movingRight = rectangle.x + rectangle.width > otherRectangle.x && rectangle.x < otherRectangle.x;
          const auto movingLeft = rectangle.x < otherRectangle.x + otherRectangle.width && rectangle.x > otherRectangle.x;

          if (movingLeft || movingRight) {
            newRectangle.x = otherRectangle.x + (movingLeft ? 1 : -1) * otherRectangle.width;
          }
        }

        if (yMoved && CheckCollisionRecs({ previousPosition.x, rectangle.y, rectangle.width, rectangle.height }, otherRectangle)) {
          auto movingDown = rectangle.y + rectangle.height > otherRectangle.y && rectangle.y < otherRectangle.y;
          auto movingUp = rectangle.y < otherRectangle.y + otherRectangle.height && rectangle.y > otherRectangle.y;

          if (movingDown || movingUp) {
            newRectangle.y = otherRectangle.y + (movingUp ? 1 : -1) * otherRectangle.height;
          }
        }

        rectangle = newRectangle;
      });

      if (m_showBounds) {
        DrawRectangleLinesEx(rectangle, 1, GREEN);
      }
    }
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
        app.generateEntity().set<component::Value<::Rectangle>>(::Rectangle { (float)x * 32, (float)y * 32, 32, 32, }).set<component::Texture>("wabbit_alpha.png").set<ColliderComponent>();
        x++;
      }
      y++;
    }
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
    .set<MovableComponent>(::Vector2 { 200, 200 })
    .set<ColliderComponent>(true);

  auto npc = app.generateEntity();
  npc
    .set<component::Value<::Rectangle>>(::Rectangle { -100, -100, 32, 32 })
    .set<component::Texture>("wabbit_alpha.png")
    .set<ColliderComponent>(false);

  app.getSystemManager().set<MoveSystem>();
  app.getSystemManager().set<CollisionSystem>();

  Map::generate(app);

  app.run();

  return 0;
}
