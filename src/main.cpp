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
  {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,3,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,1,3,1,3,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

int worldMapLevel3[mapWidth][mapHeight]=
{
  {2,2,2,2,2,2,2,3,3,3,3,3,4,4,4,1,2,2,2,2,2,3,2,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,3,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,3,0,0,3,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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

         images.emplace_back(LoadImageColors(LoadImage("pics/mossy.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/colorstone.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/purplestone.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/wood.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/redbrick.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/bluestone.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/greystone.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/eagle.png")));
         images.emplace_back(LoadImageColors(LoadImage("pics/eagle.png")));

         for (auto y = 0; y < texHeight; y++) {
           for (auto x = 0; x < texWidth; x++) {
             images[images.size() - 1][y * texWidth + x].a  /= 3;
           }
         }


fb_texture = LoadTextureFromImage(fb_image);
        };

        inline virtual void update() override {
          BeginDrawing();
          ClearBackground(BLACK);
          BeginMode2D(m_camera);

          drawFloor();
          UpdateTexture(fb_texture, pixels);
          DrawTexture(fb_texture, 0, screenHeight / 2, WHITE);
          draw();

          EndMode2D();
          DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME);
          EndDrawing();

          // for (int y = 0; y < screenHeight; y++) { for (int x = 0; x < screenWidth; x++) { pixels[y * screenWidth + x] = BLACK; }}

        }
        double posX = 18, posY = 12;  //x and y start position
        double dirX = -1, dirY = 0; //initial direction vector
        double planeX = 0, planeY = 0.5; //the 2d raycaster version of camera plane
                                         Color pixels[screenHeight * screenWidth];
 Image fb_image = Image {
        pixels,
        screenWidth,
        screenHeight / 2,
        1,
        PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    };
  std::vector<Texture> textures;
  std::vector<Color *> images;

      Texture2D fb_texture;

      private:
      void drawFloor() {
 //FLOOR CASTING
          float posZ = 0.5 * screenHeight;

          int drawFloor = 1;
    for(int y = screenHeight / 2; drawFloor && y < screenHeight; y++)
    {
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
      float rayDirX0 = dirX - planeX;
      float rayDirY0 = dirY - planeY;
      float rayDirX1 = dirX + planeX;
      float rayDirY1 = dirY + planeY;

      // Current y position compared to the center of the screen (the horizon)
      int p = y - screenHeight / 2;

      // Vertical position of the camera.

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
      float rowDistance = posZ / p * 2;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
      float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
      float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
      float floorX = posX + rowDistance * rayDirX0;
      float floorY = posY + rowDistance * rayDirY0;

      for(int x = 0; x < screenWidth; ++x)
      {
        // the cell coord is simply got from the integer parts of floorX and floorY
        int cellX = (int)(floorX);
        int cellY = (int)(floorY);

        // get the texture coordinate from the fractional part
        int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
        int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

        floorX += floorStepX;
        floorY += floorStepY;

        // choose texture and draw the pixel
        int floorTexture = 3;
        int ceilingTexture = 6;
        pixels[(y - screenHeight / 2) * screenWidth + x] = images[images.size() - 1][texWidth * ty + tx];

        // //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
        // color = images[ceilingTexture][texWidth * ty + tx];
        // color.a /= 2;
        // pixels[(screenHeight - y - 1) * screenWidth + x] = color;
      }
    }

      }
        inline void draw() {

          drawLevel(2);
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

        struct Hit { int side; double dist; int mapX; int mapY; };

        void drawLevel(int l) {
         auto level = l == 0 ? worldMap : l == 1 ? worldMapLevel2 : worldMapLevel3;

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

            // int hit = 0; //was there a wall hit?
            // int side; //was a NS or a EW wall hit?
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


            std::vector<Hit> hits;

            while (mapX != -1 && mapY != -1 && mapX < mapWidth && mapY < mapHeight && hits.size() < 2) {
              int hit = 0;
              int side = 0;

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
                if (mapX >= mapWidth) break;
                if (mapY >= mapHeight) break;
                //Check if ray has hit a wall
                if (level[mapX][mapY] > 0) hit = 1;
              } 

              if (hit) {
                if(side == 0) perpWallDist = (sideDistX - deltaDistX);
                else          perpWallDist = (sideDistY - deltaDistY);

                hits.emplace(hits.begin(), Hit { side, perpWallDist, mapX, mapY });
              }
            }

            if (hits.empty()) continue;

            // Hits are drawn from farest to closest
            
            int hitIdx = -1;
            for (auto &&hit: hits) {
              hitIdx++;
              //Calculate height of line to draw on screen
              int lineHeight = (int)(2 * screenHeight / hit.dist);

              //calculate lowest an highest pixel to fill in current stripe
              int drawStart = -lineHeight / 2 +screenHeight / 2;
              int drawEnd = lineHeight / 2 +screenHeight / 2;

              // drawStart -= l * lineHeight;
              // drawEnd -= l * lineHeight;

              // if(drawStart < 0)drawStart = 0;
              if(drawEnd >=screenHeight)drawEnd =screenHeight - 1;
              //texturing calculations
              int texNum = level[hit.mapX][hit.mapY] - 1; //1 subtracted from it so that texture 0 can be used!
                                                          // DebugLog("> ", hit.mapX, ", ", hit.mapY, ": ", texNum);

                                                          //calculate value of wallX
              double wallX; //where exactly the wall was hit
              if (hit.side == 0) wallX = posY + hit.dist * rayDirY;
              else           wallX = posX + hit.dist * rayDirX;
              wallX -= floor((wallX));

              //x coordinate on the texture
              int texX = int(wallX * double(texWidth));
              if(hit.side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
              if(hit.side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

              double step = 1.0 * texHeight / lineHeight;
              // Starting texture coordinate
              double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

              drawStart -= l * lineHeight;
              DrawTexturePro(textures[texNum], Rectangle { (float)texX, 0, 1, 64 }, Rectangle { (float)x, (float)drawStart, 1, (float)lineHeight }, Vector2 { 0, 0, }, 0, hit.side == 0 ? WHITE: Color { 128, 128, 128, 255});
            }
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
