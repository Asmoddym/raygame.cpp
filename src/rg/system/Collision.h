#ifndef RG_SYSTEM_COLLISION_H_
# define RG_SYSTEM_COLLISION_H_

# include "rg/components.h"
# include <algorithm>

namespace rg {
  namespace system {
    class Collision: public macro::System {
      DefineSystem(Collision, 5);

      private:
        bool m_showBounds = false;

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

      public:
        inline virtual void update() override {
          if (IsKeyPressed(KEY_B)) {
            m_showBounds = !m_showBounds;
          }
  
          std::vector<EdgeData> xPoints;
          std::vector<int> xActiveIntervals;
  
          registry.forEach<macro::component::Rectangle, component::Movable>([&](macro::Entity e) {
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

        auto &movable = entity.get<component::Movable>();
        auto &otherMovable = otherEntity.get<component::Movable>();

        Vector2 rectangleCenter = calculateCenter(rectangle);
        Vector2 otherRectangleCenter = calculateCenter(otherRectangle);

        Vector2 diff = { rectangleCenter.x - otherRectangleCenter.x, rectangleCenter.y - otherRectangleCenter.y };
        Vector2 normalized = normalize(diff);
        auto collisionRec = GetCollisionRec(rectangle, otherRectangle);

        // TODO: I should be able to remove left and/or right as I know there will be a X collision, and it should always be on the left (I think?)
        float max = 0.0f;
        unsigned int best_match = -1;
        for (unsigned int i = 0; i < 4; i++) {
          float dot_product = normalized.x * m_compass[i].x + normalized.y * m_compass[i].y;

          if (dot_product > max) {
            max = dot_product;
            best_match = i;
          }
        }

        if (best_match == LEFT || best_match == RIGHT) {
          float midDiff = collisionRec.width / 2;

          // As the algorithm begins with X coord, we know rectangle will always be the entity at the right.
          if (movable.value) {
            rectangle.x += midDiff;
          }
          if (otherMovable.value) {
            otherRectangle.x -= midDiff;
          }
        } else {
          float midDiff = collisionRec.height / 2;

          // Here, we need to check in which direction the collision occurred
          midDiff *= best_match == UP ? 1 : -1;

          if (movable.value) {
            rectangle.y += midDiff;
          }
          if (otherMovable.value) {
            otherRectangle.y -= midDiff;
          }
        }

        if (m_showBounds) {
          DrawRectangleLinesEx(rectangle, 1, movable.value ? GREEN : BLUE);
          DrawRectangleLinesEx(otherRectangle, 1, otherMovable.value ? YELLOW : BLUE);
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
    };
  }
}

#endif // !RG_SYSTEM_COLLISION_H_
