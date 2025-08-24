#include "Debug.h"
#include "engine/macro.h"
#include "raylib.h"
#define mapWidth 24
#define mapHeight 24
#define screenWidth 1280
#define screenHeight 720
#define texWidth 64
#define texHeight 64

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int worldMapLevel2[mapWidth][mapHeight]=
{
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,2,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,3,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,1,3,1,3,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


namespace rg {
  namespace system {
    class Raycast : public macro::System {
      private:
        Camera2D m_camera = { 0 };

      public:
        DefineSystem(Raycast, 16) {
          // m_camera.offset = ::Vector2 { size.x / 2.f, size.y / 2.f };
          m_camera.offset = ::Vector2 { 0, 0 };
          m_camera.rotation = 0.0f;
          m_camera.zoom = 1.0f;

          textures.emplace_back(LoadTexture("pics/mossy.png"));
          textures.emplace_back(LoadTexture("pics/colorstone.png"));
          textures.emplace_back(LoadTexture("pics/purplestone.png"));
          textures.emplace_back(LoadTexture("pics/wood.png"));
          textures.emplace_back(LoadTexture("pics/redbrick.png"));
          textures.emplace_back(LoadTexture("pics/bluestone.png"));
          textures.emplace_back(LoadTexture("pics/greystone.png"));
          textures.emplace_back(LoadTexture("pics/eagle.png"));

        };

        inline virtual void update() override {
          BeginDrawing();
          ClearBackground(BLACK);
          BeginMode2D(m_camera);
          draw();
          EndMode2D();
          DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME);
          EndDrawing();

        }
        double posX = 22, posY = 12;  //x and y start position
        double dirX = -1, dirY = 0; //initial direction vector
        double planeX = 0, planeY = 0.5; //the 2d raycaster version of camera plane

  int buffer[screenHeight][screenWidth]; // y-coordinate first because it works per scanline
  std::vector<Texture> textures;

      private:
        inline void draw() {
          drawLevel(1);
          drawLevel(0);
          float moveSpeed = 0.15;
          float rotSpeed = 0.03;
          //move forward if no wall in front of you
          if (IsKeyDown(KEY_UP))
          {
            if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
          }
          //move backwards if no wall behind you
          if (IsKeyDown(KEY_DOWN))
          {
            if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
          }
          //rotate to the right
          if (IsKeyDown(KEY_RIGHT))
          {
            //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
          }
          //rotate to the left
          if (IsKeyDown(KEY_LEFT))
          {
            //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
          }
          DrawLine(100, 100, 100 - dirX * 20, 100 + dirY * 20, WHITE);
        }

        void drawLevel(int l) {
          auto &level = l == 0 ? worldMap : worldMapLevel2;

          for(int x = 0; x < screenWidth; x++) {
            //calculate ray position and direction
            double cameraX = 2 * x / double(screenWidth) - 1; //x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            //which box of the map we're in
            int mapX = int(posX);
            int mapY = int(posY);

            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            //length of ray from one x or y-side to next x or y-side
            double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
            double perpWallDist;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?
                      //calculate step and initial sideDist
            if (rayDirX < 0)
            {
              stepX = -1;
              sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
              stepX = 1;
              sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
              stepY = -1;
              sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
              stepY = 1;
              sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            //perform DDA
            while (hit == 0)
            {
              //jump to next map square, either in x-direction, or in y-direction
              if (sideDistX < sideDistY)
              {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
              }
              else
              {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
              }
              if (mapX == -1) break;
              if (mapY == -1) break;
              //Check if ray has hit a wall
              if (level[mapX][mapY] > 0) hit = 1;
            } 

            if (!hit) continue;
            //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
            if(side == 0) perpWallDist = (sideDistX - deltaDistX);
            else          perpWallDist = (sideDistY - deltaDistY);

            //Calculate height of line to draw on screen
            int lineHeight = (int)(2 *screenHeight / perpWallDist);

            //calculate lowest an highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 +screenHeight / 2;
            // if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 +screenHeight / 2;
            if(drawEnd >=screenHeight)drawEnd =screenHeight - 1;

            if (l == 1) {
              drawStart -= lineHeight;
              drawEnd -= lineHeight;
            }

            //texturing calculations
            int texNum = level[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

            //calculate value of wallX
            double wallX; //where exactly the wall was hit
            if (side == 0) wallX = posY + perpWallDist * rayDirY;
            else           wallX = posX + perpWallDist * rayDirX;
            wallX -= floor((wallX));

            //x coordinate on the texture
            int texX = int(wallX * double(texWidth));
            if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
            if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

            DrawTexturePro(textures[texNum], Rectangle { (float)texX, 0, 1, 64 }, Rectangle { (float)x, (float)drawStart, 1, (float)lineHeight }, Vector2 { 0, 0, }, 0, side == 0 ? WHITE: Color { 255, 255, 255, 128});
          }
        }
    };
  }
}

int main() {
  macro::Application app;

  app.getSystemManager().set<rg::system::Raycast>();

  app.run();

  return 0;
}
