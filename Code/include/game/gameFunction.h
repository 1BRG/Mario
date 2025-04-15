//
// Created by Gabriel on 4/2/2025.
//

#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

#include <list>

#include "../defineuri.h"
#include "../entitati/Entitati.h"



class game {
    bool valid = true;
    shared_ptr<Entity> grid[screenHeight][screenWidth];
    list<shared_ptr<Living>> entities;
    static game* instance;
    game() = default;
public:
    static game* GetInstance();
    void setValid();
    void insertEntity(const shared_ptr<Entity> &entity);
    void deleteEntity(const shared_ptr<Entity> &entity);
    void topCollision(const shared_ptr<Living> &entity, int y) const;
    void bottomCollision(const shared_ptr<Living>& entity, int y) const;
    void rightCollision(const shared_ptr<Living> &entity, int x) const;
    void leftCollision(const shared_ptr<Living>& entity, int x) const;

    static void collision(list<shared_ptr<Living>> entities);
    void StartGameLoop();
    void draw() const;
};





#endif //GAMEFUNCTION_H
