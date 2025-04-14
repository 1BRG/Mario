//
// Created by Gabriel on 4/1/2025.
//

#ifndef ENTITATI_H
#define ENTITATI_H

#include <cmath>
#include <memory>
#include <raylib.h>
#include <vector>
#include "../defineuri.h"
using namespace std;
class Entity
{
protected:
    double coordX = 0, coordY = 0, x = 0, y = 0;
    double targetX = 0, targetY = 0;
    int health = 1;
    double speed = 0;
    bool moving = true;
    bool damage = false;
    bool updateLeft = true, updateRight = true, updateTop = true, updateBottom = true;
    Texture2D texture;
public:
    virtual ~Entity() = default;
    Entity(double x, const double y, const Texture2D &Texture);
    explicit Entity(const Texture2D &Texture);
    Entity() = default;

    [[nodiscard]] double coord_x() const;

    [[nodiscard]] double coord_y() const;

    [[nodiscard]] double height() const;

    [[nodiscard]] double width() const;

    [[nodiscard]] double target_x() const;

    [[nodiscard]] double target_y() const;

    bool danger() const;
    virtual void draw();
    virtual void update();
    virtual void collision(Entity &other, int directie = 0);
    virtual void gravity(){}
    virtual void moveToTarget();

    ///
    virtual void setLastY(){}
    ///
};

class Player : public Entity {
    double lastY = screenHeight;
    bool canJump = true, cont = true, isJumping = false;
public:
    Player(double x,  double y);
    Player();
    void handleInput();
    void moveX();
    void moveY();
    void update() override;
    void collision(Entity &other, int directie = 0) override;
    void collision();
    void moveToTarget() override;
    void gravity() override;
    void setLastY() override;
};
class Enviroment : public Entity
{
public:
    Enviroment(double x, double y);
    Enviroment();
};

#endif //ENTITATI_H
