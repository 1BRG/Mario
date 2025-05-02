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
    int yy = entity->coord_y(), xx = entity->coord_x();
    for (int i = yy; i < yy + entity->height() && i < screenHeight - 1; i++)
        for (int j = xx; j < xx + entity->width() && j < screenWidth - 1; j++)
                grid[i][j] = entity;
}

void game::deleteEntity(const shared_ptr<Entity> &entity)
{
    int yy = entity->coord_y(), xx = entity->coord_x();
    for (int i = yy; i < yy + entity->height() && i < screenHeight - 1; i++)
        for (int j = xx; j < xx + entity->width() && j < screenWidth - 1; j++)
            grid[i][j] = nullptr;
}

void game::topCollision(const shared_ptr<Living> &entity) const
{
    for (const auto& env : environment) {
        if (entity->topCollision(env))
            entity->collision(*env, -1);
    }
    for (const auto& env : entities) {
        if (entity->topCollision(env))
            entity->collision(*env, -1), env->collision(*entity, 1);
    }
}

void game::bottomCollision(const shared_ptr<Living>& entity) const
{
    for (auto env : environment) {
        if (entity->bottomCollision(env))
            entity->collision(*env, 1);
    }
    for (const auto& env : entities) {

        if (entity->bottomCollision(env) && entity != env)
            entity->collision(*env, 1), env->collision(*entity, -1);
    }
}

void game::leftCollision(const shared_ptr<Living>& entity) const
{
    for (const auto& env : environment) {
        if (entity->leftCollision(env))
            entity->collision(*env, -2);
    }
    for (const auto& env : entities) {
        if (entity->leftCollision(env) && entity != env)
            entity->collision(*env, -2), env->collision(*entity, 2);
    }
}

void game::rightCollision(const shared_ptr<Living> &entity) const
{
    for (const auto& env : environment) {
        if (entity->rightCollision(env))
            entity->collision(*env, 2);
    }
    for (const auto& env : entities) {
        if (entity->rightCollision(env) && entity != env)
            entity->collision(*env, 2), env->collision(*entity, -2);
    }
}
void game::collision(const list<shared_ptr<Living>> &entities)
{
    game* currentGame = GetInstance();
    for (const auto& entity : entities)
    {
        //if (currentGame->inScreenEntity(entity)) {
            currentGame->bottomCollision(entity);
            //  currentGame->deleteEntity(entity);
            currentGame->leftCollision(entity);
            currentGame->rightCollision(entity);
            currentGame->topCollision(entity);
     //   }
  //      entity->moveToTarget();
    //    currentGame->insertEntity(entity);
    }


}
void game::setLevel(int k) {
    string filename = "../Code/Levels/level" + to_string(k) + ".txt";
    ifstream f(filename);
    string line;
    level.clear();

    // 0 liber
    // 1 brick
    // P player
    // 2 tortoise
    int n = 1;

    while (getline(f, line)) {
        for (long long unsigned int i = 0; i < line.length(); i++) {
            {
                if (line[i] == '1') {
                    shared_ptr<Entity> a = make_shared<Entity>((i) * 64, n * 64, BrickTexture);
                    level.push_back(a);
                }
                else if (line[i] == '2') {
                    shared_ptr<Entity> a = make_shared<Turtle>((i) * 64, n * 64);
                  level.push_back(a);
                }
                else if (line[i] == 'P') {
                    shared_ptr<Entity> a = make_shared<Player>((i) * 64, n * 64);
                    level.push_back(a);
                }
            }
        }
        n ++;
    }
    f.close();
    level.sort([] (const shared_ptr<Entity> &a, const shared_ptr<Entity> &b) -> bool {
        return a->coord_x() < b->coord_x();
    });
}
void game::setEntities() {
    entities.clear();
    environment.clear();
    for (int i = 0; i < screenHeight; i ++)
        for (int j = 0; j < screenWidth; j ++)
            grid[i][j] = nullptr;
    for (auto entity : level) {

        if (dynamic_pointer_cast<Living>(entity) != nullptr)
            entities.push_back(dynamic_pointer_cast<Living>(entity));
        else environment.push_back(entity);
      //  insertEntity(entity);
    }
}

void game::setValid()
{
    ///daca player.health <= 0 false
}
bool game::inScreenEntity(shared_ptr<Entity> entity) const {
    if (entity->coord_x() <= -entity->width() - cameraX || entity->coord_x() - cameraX >= screenWidth
    || entity->coord_y() < -entity->height() || entity->coord_y() > screenHeight)
        return false;
    return true;
}
void game::StartGameLoop()
{
    InitWindow(screenWidth, screenHeight, "Hello World");
    SetTargetFPS(144);
    ClearBackground(GREEN);
    setLevel(1);
    setEntities();
    float fr = GetFrameTime();
    fr = 0;
    int o = 0;
    while(!WindowShouldClose())
    {
        o ++;
        if (o > 2)
            fr = GetFrameTime();
       // dt = 0.0096;
        BeginDrawing();
        ClearBackground(GREEN);
        for (auto it = entities.begin(); it != entities.end(); ) {
            (*it)->deltaTime(fr);
            if (!(*it)->isAlive()) {
                deleteEntity(*it);
                it = entities.erase(it);
            } else if (inScreenEntity(*it)){
                (*it)->setLastY();
                ++it;
            }
            else ++it;
        }
        for (const auto& entity : entities)
            //if (inScreenEntity(entity))
               bottomCollision(entity);
        for (const auto& entity : entities)
           // if (inScreenEntity(entity))
                entity->moveToTarget();
        for (const auto& entity : entities)
           // if (inScreenEntity(entity))
               entity->update();
        collision(entities);


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

        for (const auto& entity : entities)
          //  if (inScreenEntity(entity))
            entity->moveToTarget();




        if (entities.front()->coord_x() - cameraX > screenWidth * 1. / 2) {
            float dec = entities.front()->coord_x() - cameraX - screenWidth * 1. / 2;
            cameraX += dec;

        }
        draw();
        EndDrawing();
       // cout << GetFPS() << "FPS" << endl;


    }
}
void game::draw() const
{
    game* currentGame = GetInstance();
    for (const auto& entitate: environment)
        if (currentGame->inScreenEntity(entitate))
            entitate->draw(cameraX);
    for (const auto& entitate: entities)
        if (currentGame->inScreenEntity(entitate))
        entitate->draw(cameraX);
}
