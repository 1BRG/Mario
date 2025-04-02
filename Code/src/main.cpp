#include <iostream>
#include <raylib.h>
#include <vector>

#include "../include/Entitati.h"
#include "../include/defineuri.h"
using namespace std;


int main()
{
    game* Game = game::GetInstance();
   // Game->Initialize(1000, 800, false, true);

    Game->StartGameLoop();
  return 0;
}
