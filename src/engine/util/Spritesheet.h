#ifndef RG_COMPONENT_SPRITESHEET_H_
# define RG_COMPONENT_SPRITESHEET_H_

# include "raylib.h"
# include <string>

namespace macro {
    class Spritesheet {
        unsigned int m_index = 0;
        bool m_loaded = false;
        std::string m_path;
        unsigned int m_tiles;
        Texture2D m_texture;

      public:
        inline Spritesheet() {}
        inline virtual ~Spritesheet() { if (m_loaded) UnloadTexture(m_texture); }

        inline void loadFromFile(std::string const &texturePath) {
          m_path = texturePath;
          m_texture = LoadTexture(texturePath.c_str());
          m_tiles = (int)(m_texture.width / m_texture.height);

          m_loaded = true;
        }

        inline void draw(::Rectangle &dest) {
          // Using height because tiles are (at least for now) squares
          float sheetX = (float)m_index * m_texture.height;

          DrawTexturePro(m_texture, Rectangle { sheetX, 0, 32, 32 }, dest, Vector2 { 0, 0 }, 0, WHITE);
        }

        inline void update() {
          m_index++;
          m_index %= m_tiles;
        }

        inline void setIndex(unsigned int i) { m_index = i; }
    };
  }

#endif // !RG_COMPONENT_SPRITESHEET_H_
