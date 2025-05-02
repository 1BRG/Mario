//
// Created by Gabriel on 4/2/2025.
//

#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

#include <list>

#include "../defineuri.h"
#include "../entitati/includeAll.h"
#include <fstream>
#include <memory>
class game {
    bool valid = true;
    float cameraX = 0, cameraY = 0;
    shared_ptr<Entity> grid[screenHeight][screenWidth];
    list<shared_ptr<Living>> entities;
    list<shared_ptr<Entity>> level;
    list<shared_ptr<Entity>> environment;
    static game* instance;
    game() = default;
public:
    static game* GetInstance();
    void setLevel(int k);
    void setEntities();
    void setValid();

    bool inScreenEntity(shared_ptr<Entity> entity) const;

    void insertEntity(const shared_ptr<Entity> &entity);
    void deleteEntity(const shared_ptr<Entity> &entity);
    void topCollision(const shared_ptr<Living> &entity, int y) const;
    void bottomCollision(const shared_ptr<Living>& entity, int y) const;
    void rightCollision(const shared_ptr<Living> &entity, int x) const;
    void leftCollision(const shared_ptr<Living>& entity, int x) const;

    static void collision(const list<shared_ptr<Living>> &entities);
    void StartGameLoop();
    void draw() const;
};





#endif //GAMEFUNCTION_H
