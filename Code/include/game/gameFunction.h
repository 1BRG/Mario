//
// Created by Gabriel on 4/2/2025.
//

#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

#include <list>

#include "../defineuri.h"
#include "../entitati/includeAll.h"
#include <string>
#include <iostream>
#include <fstream>
#include <memory>


class game {
    std::shared_ptr<Audio> bgMusic;
    bool valid = true;
    float cameraX {0}, cameraY {0};
    std::shared_ptr<Entity> grid[screenHeight][screenWidth];
    std::list<std::shared_ptr<Living> > entities;
    std::list<std::shared_ptr<Entity> > level;
    std::list<std::shared_ptr<Entity> > environment;
    std::list<std::shared_ptr<MovebleEnvironment>> movEnv;
    static game *instance;

    game() = default;

public:
    static game *GetInstance();

    void setLevel(int k);

    void setEntities();

    static void setValid();

    bool inScreenEntity(const std::shared_ptr<Entity> &entity) const;

    void insertEntity(const std::shared_ptr<Entity> &entity);

    void deleteEntity(const std::shared_ptr<Entity> &entity);

    void topCollision(const std::shared_ptr<Living> &entity) const;

    void bottomCollision(const std::shared_ptr<Living> &entity) const;

    void rightCollision(const std::shared_ptr<Living> &entity) const;

    void leftCollision(const std::shared_ptr<Living> &entity) const;

    static void collision(const std::list<std::shared_ptr<Living> > &entities);

    void setFPS(float &fr, int o);

    void StartGameLoop();

    void draw() const;
};


#endif //GAMEFUNCTION_H
