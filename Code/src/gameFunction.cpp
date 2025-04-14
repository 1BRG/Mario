//
// Created by Gabriel on 4/2/2025.
//

#include "../include/game/gameFunction.h"

#include <iostream>
game* game::instance = nullptr;

game* game::GetInstance()
{
    if(instance == nullptr)
    {
        instance = new game();
    }
    return instance;
}

void game::insertEntity(const shared_ptr<Entity> &entity)
{
    int y = entity->coord_y(), x = entity->coord_x();
    for (int i = y; i < y + entity->height() && i < screenHeight - 1; i++)
        for (int j = x; j < x + entity->width() && j < screenWidth - 1; j++)
                grid[i][j] = entity;
}

void game::deleteEntity(const shared_ptr<Entity> &entity)
{
    int y = entity->coord_y(), x = entity->coord_x();
    for (int i = y; i < y + entity->height() && i < screenHeight - 1; i++)
        for (int j = x; j < x + entity->width() && j < screenWidth - 1; j++)
            // for (int p = 0; p < grid[i][j].size(); p++)
            // if (grid[i][j][p] == entity)
            // grid[i][j].erase(grid[i][j].begin() + p);
            grid[i][j] = nullptr;
}

void game::topCollision(const shared_ptr<Entity> &entity, int y = 1) const
{
    int x = entity->coord_x();
    y = entity->target_y() - 1;
    for (int i = x; i <= x + entity->width() && i < screenWidth - 1 && y >= 0 && y < screenHeight - 1; i++)
        //for (int j = 0; j < grid[y][i].size(); j ++)
            if (grid[y][i] != nullptr)
        entity->collision(*grid[y][i], -1);
}

void game::bottomCollision(const shared_ptr<Entity>& entity, int y = 1) const
{
    int x = entity->coord_x();
    y = entity->target_y() + entity->height() + 1;
    for (int i = x; i <= x + entity->width() && i < screenWidth - 1 && y >= 0 && y < screenHeight - 1; i++)
        // for (int j = 0; j < grid[y][i].size(); j ++)
            if (grid[y][i] != nullptr)
        entity->collision(*grid[y][i], 1);
}

void game::leftCollision(const shared_ptr<Entity>& entity, int x = 1) const
{
    int y = entity->coord_y();
    x = entity->target_x() - 1;
    for (int i = y; i <= y + entity->height() && i < screenHeight - 1  && x >= 0 && x < screenWidth - 1; i++)
        //for (int j = 0; j < grid[i][x].size(); j ++)
            if (grid[i][x] != nullptr)
        entity->collision(*grid[i][x]);
}

void game::rightCollision(const shared_ptr<Entity> &entity, int x = 1) const
{
    int y = entity->coord_y();
    x = entity->target_x() + entity->width() + 1;
    for (int i = y; i <= y + entity->height() && i < screenHeight - 1 && x >= 0 && x < screenWidth - 1; i++)
        if (grid[i][x] != nullptr)
        entity->collision(*grid[i][x]);
}
void game::collision(list<shared_ptr<Entity>> entities)
{
    game* currentGame = GetInstance();
    for (auto entity : entities)
    {
        currentGame->bottomCollision(entity);
        currentGame->topCollision(entity);
        currentGame->rightCollision(entity);
        currentGame->leftCollision(entity);
    }

}

void game::setValid()
{
    ///daca player.health <= 0 false
}
void game::StartGameLoop()
{
    InitWindow(screenWidth, screenHeight, "Hello World");
    SetTargetFPS(144);
    ClearBackground(GREEN);
    Player player(screenWidth / 2, screenHeight / 2);
    shared_ptr<Entity> a = make_shared<Entity>(screenWidth / 2, screenHeight / 2 + BrickTexture.height + 200, BrickTexture);
    entities.push_back(make_shared<Player>(player));
    entities.push_back(a);
    insertEntity(a);
    for (int i = 0; i < screenWidth; )
    {
        shared_ptr<Entity> a = make_shared<Entity>(i, screenHeight - BrickTexture.height, BrickTexture);

        i = i + BrickTexture.width;
        entities.push_back(a);
        insertEntity(a);
    }
    /*
    for (int i = 0; i < screenHeight; i ++) {
        for (int j = 0; j < screenWidth; j++) {
            if (grid[i][j] != nullptr)
                cout << i << " " << j << endl;
         //   else cout << 0;
        }
        cout << endl;
    }
    */

  //  ToggleFullscreen();
   // int ct = 0;
    while(!WindowShouldClose())
    {
        //ct ++;
        //cout << ct << "\n";

        BeginDrawing();
       // player.update();
        for (auto entity : entities) {
            entity->setLastY();
            break;
        }
        ClearBackground(GREEN);
        for (auto entity : entities)
            bottomCollision(entity);
        for (auto entity : entities)
            entity->update();
        collision(entities);
        for (auto entity : entities)
            entity->moveToTarget();
      //  player.draw();
        draw();
        EndDrawing();
    }
}
void game::draw() const
{
    for (const auto& entitate: entities)
        entitate->draw();
}
