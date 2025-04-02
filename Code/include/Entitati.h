//
// Created by Gabriel on 4/1/2025.
//

#ifndef ENTITATI_H
#define ENTITATI_H

#include <cmath>
#include <memory>
#include <raylib.h>
#include <vector>
#include "defineuri.h"
using namespace std;
class Entity
{
protected:
    double coordX = 0, coordY = 0, x = 0, y = 0;

    int health = 1;
    double speed = 0;
    bool moving = true;
    bool damage = false;
    Texture2D texture;
public:
    virtual ~Entity() = default;
    Entity(double x, const double y, const Texture2D &Texture);
    explicit Entity(const Texture2D &Texture);
    Entity() = default;

    [[nodiscard]] double coord_x() const;

    [[nodiscard]] double coord_y() const;

    [[nodiscard]] double x1() const;

    [[nodiscard]] double y1() const;
    bool danger() const;
    virtual void draw();
    virtual void update();
    virtual void colision(Entity &other);
    virtual void gravity(){}
};

class Player : public Entity {

    double lastY = 0;
    bool canJump = true, cont = true, isJumping = false;
public:
    Player(double x, const double y);
    Player();
    void handleInput();
    void moveX();
    void moveY();
    void update() override;
    void colision(Entity &other) override;
    void gravity() override;
};
class Enviroment : public Entity
{
public:
    Enviroment(const double x, const double y);
    Enviroment();
};

class game {
    bool valid = true;
    shared_ptr<Entity> grid[screenHeight][screenHeight];
    vector<shared_ptr<Entity>> entities;

    static game* instance;
    game() {}
public:
    static game* GetInstance();
    void setValid();
    void insert(const shared_ptr<Entity> &entity);
    void deleteEntity(const shared_ptr<Entity> &entity);
    void topColision(const shared_ptr<Entity> &entity, int y) const;
    void bottomColision(const shared_ptr<Entity>& entity, int y) const;
    void rightColision(const shared_ptr<Entity> &entity, int x) const;
    void leftColision(const shared_ptr<Entity>& entity, int x) const;

    static void colision(const shared_ptr<Entity> &other);
    void StartGameLoop();
    void draw();
};


#endif //ENTITATI_H
