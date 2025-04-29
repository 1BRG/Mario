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
void game::collision(const list<shared_ptr<Living>> &entities)
{
    game* currentGame = GetInstance();
    for (const auto& entity : entities)
    {
        if (currentGame->inScreenEntity(entity)) {
            //  currentGame->deleteEntity(entity);

            currentGame->bottomCollision(entity);
            currentGame->topCollision(entity);
            currentGame->rightCollision(entity);
            currentGame->leftCollision(entity);
        }

      //  entity->moveToTarget();
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
        for (int i = 0; i < line.length(); i++) {
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
        insertEntity(entity);
    }
}

void game::setValid()
{
    ///daca player.health <= 0 false
}
bool game::inScreenEntity(shared_ptr<Entity> entity) {
    if (entity->coord_x() <= -entity->width() || entity->coord_x() >= screenWidth
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
    float dt = GetFrameTime();
    dt = 0;
    int o = 0;
    while(!WindowShouldClose())
    {
        o ++;
        if (o > 2)
            dt = GetFrameTime();
        dt = 0.0096;
        BeginDrawing();
        ClearBackground(GREEN);
        for (auto it = entities.begin(); it != entities.end(); ) {
            (*it)->deltaTime(dt);
            if (!(*it)->isAlive() || (*it)->coord_x() <= -(*it)->width()) {
                deleteEntity(*it);
                it = entities.erase(it);
            } else if (inScreenEntity(*it)){
                (*it)->setLastY();
                ++it;
            }
            else ++it;
        }
        for (auto it = environment.begin(); it != environment.end(); ) {
            if ((*it)->coord_x() <= -(*it)->width()) {
            //    deleteEntity(*it);
                it = environment.erase(it);
            }
            else ++it;
        }
        for (const auto& entity : entities)
            if (inScreenEntity(entity))
               bottomCollision(entity);
        for (const auto& entity : entities)
            if (inScreenEntity(entity))
               entity->update();
        collision(entities);

        for (const auto& entity : entities)
            if (inScreenEntity(entity))
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

        for (const auto& entity : entities)
            if (inScreenEntity(entity))
            entity->moveToTarget();

        for (const auto& entity : entities)
            if (inScreenEntity(entity))
            insertEntity(entity);



        if (int(entities.front()->coord_x()) > screenWidth / 2) {
            int dec = int(entities.front()->coord_x()) - int(screenWidth / 2);
            vector <shared_ptr<Entity>> v;
            for (const auto& entity : entities) {
                int ct = 0;
                if (!inScreenEntity(entity))
                    ct = 1;
                entity->decreaseX(dec);
                if (inScreenEntity(entity))
                    ct ++;
                if (ct == 2)
                    v.push_back(entity);
                deleteEntity(entity);
            }
         //   entities.front()->decreaseX(dec);
            for (const auto& entity : environment) {
                int ct = 0;
                if (!inScreenEntity(entity))
                    ct = 1;
                entity->decreaseX(dec);
                if (inScreenEntity(entity))
                    ct ++;
                if (ct == 2)
                    v.push_back(entity);
                deleteEntity(entity);
            }
            for (int i = 0; i < screenHeight; i ++) {
                for (int j = 0; j < screenWidth - dec; j ++)
                    grid[i][j] = grid[i][j + dec];
                for (int j = screenWidth - dec; j < screenWidth; j ++)
                    grid[i][j] = nullptr;
            }

            for (const auto& entity : entities)
                if (inScreenEntity(entity))
                    insertEntity(entity);
            for (const auto& entity : environment)
                if (inScreenEntity(entity))
                    insertEntity(entity);

           // for (auto entity: v)
             //   insertEntity(entity);
        }
        draw();
        EndDrawing();
        cout << GetFPS() << "FPS" << endl;
    }
}
void game::draw() const
{
    game* currentGame = GetInstance();
    for (const auto& entitate: environment)
        if (currentGame->inScreenEntity(entitate))
            entitate->draw();
    for (const auto& entitate: entities)
        if (currentGame->inScreenEntity(entitate))
        entitate->draw();
}
