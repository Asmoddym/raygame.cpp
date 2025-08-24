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
fb_texture = LoadTextureFromImage(fb_image);
        };

        inline virtual void update() override {
          BeginDrawing();
          ClearBackground(BLACK);
          BeginMode2D(m_camera);
          draw();

          UpdateTexture(fb_texture, pixels);
          DrawTexture(fb_texture, 0, 0, WHITE);

          EndMode2D();
          DrawText(Concatenate(GetFPS(), " FPS (", Timer::since(), "ms)").c_str(), 10, 10, 20, LIME);
          EndDrawing();

          for (int y = 0; y < screenHeight; y++) { for (int x = 0; x < screenWidth; x++) { pixels[y * screenWidth + x] = BLACK; }}

        }
        double posX = 18, posY = 12;  //x and y start position
        double dirX = -1, dirY = 0; //initial direction vector
        double planeX = 0, planeY = 0.5; //the 2d raycaster version of camera plane
                                         Color pixels[screenHeight * screenWidth];
 Image fb_image = {
        .data = pixels,
        .width = screenWidth,
        .height = screenHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
    };
  std::vector<Texture> textures;
  std::vector<Color *> images;

      Texture2D fb_texture;


      private:
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
          auto &level = l == 0 ? worldMap : l == 1 ? worldMapLevel2 : worldMapLevel3;

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
              int lineHeight = (int)(screenHeight / hit.dist);

              //calculate lowest an highest pixel to fill in current stripe
              int drawStart = -lineHeight / 2 +screenHeight / 2;
              int drawEnd = lineHeight / 2 +screenHeight / 2;

              drawStart -= l * lineHeight;
              drawEnd -= l * lineHeight;

              if(drawStart < 0)drawStart = 0;
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

              for (int y = drawStart; y < drawEnd; y++) {
                int texY = (int)texPos & (texHeight - 1);
                texPos += step;

                // DebugLog("> ", texY, ", ", texY, ", ", y, ", ", x);
                // DebugLog(texY, ", ", texX, ", ", texNum, ", ", hit.mapX, ", ", hit.mapY);
                pixels[y * screenWidth + x] = images[texNum][texY * texWidth + texX];
                // DebugLog("OK");
                // DebugLog("OK");
              }


              bool drawCeiling = false;
              bool drawFloor = hitIdx == hits.size() - 1 && l == 0;

              // Calculate ceiling
              if (drawCeiling || drawFloor) {
                // if (drawCeiling) drawStart -= (l + 1) * lineHeight;



                //FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
                double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

                //4 different wall directions possible
                if(hit.side == 0 && rayDirX > 0)
                {
                  floorXWall = hit.mapX;
                  floorYWall = hit.mapY + wallX;
                }
                else if(hit.side == 0 && rayDirX < 0)
                {
                  floorXWall = hit.mapX + 1.0;
                  floorYWall = hit.mapY + wallX;
                }
                else if(hit.side == 1 && rayDirY > 0)
                {
                  floorXWall = hit.mapX + wallX;
                  floorYWall = hit.mapY;
                }
                else
                {
                  floorXWall = hit.mapX + wallX;
                  floorYWall = hit.mapY + 1.0;
                }

                double distWall, distPlayer, currentDist;

                distWall =hit.dist;
                distPlayer = 0.0;

                if (drawEnd < 0) drawEnd = screenHeight; //becomes < 0 when the integer overflows

                //draw the ceiling from drawEnd to the bottom of the screen
                for(int y = drawEnd + 1; y < screenHeight; y++)
                {
                  currentDist = screenHeight / (2.0 * y - screenHeight); //you could make a small lookup table for this instead

                  double weight = (currentDist - distPlayer) / (distWall - distPlayer);

                  double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
                  double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

                  int floorTexX, floorTexY;
                  floorTexX = int(currentFloorX * texWidth) % texWidth;
                  floorTexY = int(currentFloorY * texHeight) % texHeight;

                  //ceiling (symmetrical!)
                  // - offset for levels
                  if (drawCeiling) pixels[(screenHeight - y) * screenWidth + x] = images[6][texWidth * floorTexY + floorTexX];
                  if (drawFloor) pixels[y * screenWidth + x] = images[3][texWidth * floorTexY + floorTexX];
                }
              }


              // // Calculate floor
              // if (hitIdx == hits.size() - 1 && l == 0) {
              // texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
              //
              //
              //   //FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
              //   double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall
              //
              //   //4 different wall directions possible
              //   if(hit.side == 0 && rayDirX > 0)
              //   {
              //     floorXWall = hit.mapX;
              //     floorYWall = hit.mapY + wallX;
              //   }
              //   else if(hit.side == 0 && rayDirX < 0)
              //   {
              //     floorXWall = hit.mapX + 1.0;
              //     floorYWall = hit.mapY + wallX;
              //   }
              //   else if(hit.side == 1 && rayDirY > 0)
              //   {
              //     floorXWall = hit.mapX + wallX;
              //     floorYWall = hit.mapY;
              //   }
              //   else
              //   {
              //     floorXWall = hit.mapX + wallX;
              //     floorYWall = hit.mapY + 1.0;
              //   }
              //
              //   double distWall, distPlayer, currentDist;
              //
              //   distWall =hit.dist;
              //   distPlayer = 0.0;
              //
              //   if (drawEnd < 0) drawEnd = screenHeight; //becomes < 0 when the integer overflows
              //
              //   //draw the floor from drawEnd to the bottom of the screen
              //   for(int y = drawEnd + 1; y < screenHeight; y++)
              //   {
              //     currentDist = screenHeight / (2.0 * y - screenHeight); //you could make a small lookup table for this instead
              //
              //     double weight = (currentDist - distPlayer) / (distWall - distPlayer);
              //
              //     double currentFloorX = weight * floorXWall + (2.0 - weight) * posX;
              //     double currentFloorY = weight * floorYWall + (2.0 - weight) * posY;
              //
              //     int floorTexX, floorTexY;
              //     floorTexX = int(currentFloorX * texWidth) % texWidth;
              //     floorTexY = int(currentFloorY * texHeight) % texHeight;
              //
              //     pixels[y * screenWidth + x] = images[3][texWidth * floorTexY + floorTexX];
              //   }
              // }
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
