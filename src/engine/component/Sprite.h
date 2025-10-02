#ifndef RG_COMPONENT_SPRITE_H_
# define RG_COMPONENT_SPRITE_H_

# include <unordered_map>
# include <string>
# include "Component.h"
# include "engine/util/Spritesheet.h"

namespace macro {
  namespace component {
    struct Sprite : public macro::Component {
      private:
        std::unordered_map<int, Spritesheet> m_states;
        unsigned int m_currentStateIndex = 0;

      public:
        inline Sprite(std::unordered_map<int, std::string> cfg) {
          for (auto &&item: cfg) {
            m_states[item.first].loadFromFile(item.second);
          }
        }

        inline unsigned int getState() { return m_currentStateIndex; }
        inline void setState(int state) {
          m_currentStateIndex = state;
          getCurrentState().setIndex(0);
        }

        inline void draw(::Rectangle &r) { getCurrentState().draw(r); }
        inline void update() { getCurrentState().update(); }

      private:
        inline Spritesheet &getCurrentState() { return m_states.at(m_currentStateIndex); }

    };
  }
}

#endif // !RG_COMPONENT_SPRITE_H_
