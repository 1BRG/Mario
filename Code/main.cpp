#include <iostream>
#include <raylib.h>
#include <vector>

#include "Entitati.h"
#include "defineuri.h"
using namespace std;

int main()
{
  InitWindow(screenWidth, screenHeight, "Hello World");
  SetTargetFPS(60);
  ClearBackground(GREEN);
    Game game;
  Player player(0 / 2, 0 / 2);
    vector<Entity> v;
    for (int i = 0; i < screenWidth; ) {
        Brick a(i, screenHeight - BrickTexture.height);
        v.push_back(a);
        i = i + BrickTexture.width;
    }
  while(!WindowShouldClose())
  {

     BeginDrawing();
      ClearBackground(GREEN);
      player.update();
      player.draw();
      game.draw(v);
     EndDrawing();
  }
  return 0;
}
