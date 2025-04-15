//
// Created by Gabriel on 4/2/2025.
//

#include "../include/game/gameFunction.h"

#include <iostream>
int ct = 0;
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
            grid[i][j] = nullptr;
}

void game::topCollision(const shared_ptr<Living> &entity, int y = 1) const
{
    int x = entity->coord_x();
    y = entity->target_y() - 2;
    for (int i = x; i <= x + entity->width() && i < screenWidth - 1 && y >= 0 && y < screenHeight - 1; i++)
        //for (int j = 0; j < grid[y][i].size(); j ++)
            if (grid[y][i] != nullptr && grid[y][i] != entity)
        entity->collision(*grid[y][i], -1), grid[y][i]->collision(*entity, 1);
}

void game::bottomCollision(const shared_ptr<Living>& entity, int y = 1) const
{
    int x = entity->coord_x();
    y = entity->target_y() + entity->height() + 1;
    for (int i = x; i <= x + entity->width() && i < screenWidth - 1 && y >= 0 && y < screenHeight - 1; i++)
        // for (int j = 0; j < grid[y][i].size(); j ++)
            if (grid[y][i] != nullptr && grid[y][i] != entity)
        entity->collision(*grid[y][i], 1), grid[y][i]->collision(*entity, -1);
}

void game::leftCollision(const shared_ptr<Living>& entity, int x = 1) const
{
    int y = entity->coord_y();
    x = entity->target_x() - 2;
    for (int i = y; i <= y + entity->height() && i < screenHeight - 1  && x >= 0 && x < screenWidth - 1; i++)
        //for (int j = 0; j < grid[i][x].size(); j ++)
            if (grid[i][x] != nullptr && grid[i][x] != entity)
        entity->collision(*grid[i][x], -2), grid[i][x]->collision(*entity, 2);
}

void game::rightCollision(const shared_ptr<Living> &entity, int x = 1) const
{
    int y = entity->coord_y();
    x = entity->target_x() + entity->width() + 1;
    for (int i = y; i <= y + entity->height() && i < screenHeight - 1 && x >= 0 && x < screenWidth - 1; i++)
        if (grid[i][x] != nullptr && grid[i][x] != entity)
        entity->collision(*grid[i][x], 2), grid[i][x]->collision(*entity, -2);
}
void game::collision(list<shared_ptr<Living>> entities)
{
    game* currentGame = GetInstance();
    for (auto entity : entities)
    {
      //  currentGame->deleteEntity(entity);

        currentGame->bottomCollision(entity);
        currentGame->topCollision(entity);
        currentGame->rightCollision(entity);
        currentGame->leftCollision(entity);

      //  entity->moveToTarget();
    //    currentGame->insertEntity(entity);
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
    Turtle turtle(screenWidth / 2 + 400, screenHeight / 2);
    shared_ptr<Entity> a = make_shared<Entity>(screenWidth / 2, screenHeight / 2 + BrickTexture.height + 200, BrickTexture);
    entities.push_back(make_shared<Player>(player));
    Turtle turtle1(screenWidth / 2 - 400, screenHeight / 2);
    entities.push_back(make_shared<Turtle>(turtle));

    entities.push_back(make_shared<Turtle>(turtle1));
    list<shared_ptr<Entity>> enviroment;
    enviroment.push_back(a);
    insertEntity(a);
    a = make_shared<Entity>(124, screenHeight - 2 * BrickTexture.height, BrickTexture);
    enviroment.push_back(a);
    insertEntity(a);
    a = make_shared<Entity>(screenWidth - 124, screenHeight - 2 * BrickTexture.height, BrickTexture);
    enviroment.push_back(a);
    insertEntity(a);

    insertEntity(make_shared<Entity>(turtle)), insertEntity(make_shared<Entity>(player));
    for (int i = 0; i < screenWidth; )
    {
        shared_ptr<Entity> a = make_shared<Entity>(i, screenHeight - BrickTexture.height, BrickTexture);
        i = i + BrickTexture.width;
        enviroment.push_back(a);
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
   // ToggleFullscreen();
   // int ct = 0;
    /*
    for (int i = 0; i < screenHeight; i ++) {
        for (int j = 0; j < screenWidth; j++) {
            if (grid[i][j] != nullptr)
                DrawPixel(j, i, BLACK);
            else DrawPixel(j, i, GREEN);
            if (grid[i][j] != nullptr) {
                if ((i - grid[i][j]->coord_y() >= 0 && i - grid[i][j]->coord_y() < 10) && (j - grid[i][j]->coord_x() >= 0 && j - grid[i][j]->coord_x() < 10)) {
                    DrawPixel(j, i, RED);
                }
            }
            //   else cout << " ";
        }
        cout << endl;
    }
    */
    while(!WindowShouldClose())
    {
        ct ++;
        BeginDrawing();
        ClearBackground(GREEN);

        for (auto it = entities.begin(); it != entities.end(); ) {
            if (!(*it)->isAlive()) {
                deleteEntity(*it);
                it = entities.erase(it);
            } else {
                (*it)->setLastY();
                ++it;
            }
        }
        for (auto entity : entities)
            bottomCollision(entity);
        for (auto entity : entities)
            entity->update();
        collision(entities);

        for (auto entity : entities)
           deleteEntity(entity);

        /*
        for (int i = 0; i < screenHeight; i ++) {
            for (int j = 0; j < screenWidth; j++) {
                if (grid[i][j] != nullptr)
                    DrawPixel(j, i, BLACK);
                else DrawPixel(j, i, GREEN);
                if (grid[i][j] != nullptr) {
                    if ((i - grid[i][j]->coord_y() >= 0 && i - grid[i][j]->coord_y() < 10) && (j - grid[i][j]->coord_x() >= 0 && j - grid[i][j]->coord_x() < 10)) {
                        DrawPixel(j, i, RED);
                    }
                }
                //   else cout << " ";
            }
            cout << endl;
        }
        */

        for (auto entity : entities)
            entity->moveToTarget();

        for (auto entity : entities)
            insertEntity(entity);

        for (const auto& entitate: enviroment)
            entitate->draw();
        draw();
        EndDrawing();
        cout << GetFPS() << "FPS" << endl;
    }
}
void game::draw() const
{
    for (const auto& entitate: entities)
        entitate->draw();
}
