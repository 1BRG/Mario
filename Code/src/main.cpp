#include <iostream>
#include <raylib.h>
#include <vector>

#include "../include/entitati/includeAll.h"
#include "../include/defineuri.h"
#include "../include/game/gameFunction.h"
using namespace std;


int main()
{
    game* Game = game::GetInstance();
   // Game->Initialize(1000, 800, false, true);

    Game->StartGameLoop();
  return 0;
}
