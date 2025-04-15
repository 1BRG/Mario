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
    bool moving = true;
    int damage = 0;
    bool updateLeft = true, updateRight = true, updateTop = true, updateBottom = true;
    Texture2D texture;
public:
    virtual ~Entity() = default;
    virtual void incomingDamage() {}
    virtual void collision(Entity &other, int direction);
    Entity(double x, const double y, const Texture2D &Texture);
    explicit Entity(const Texture2D &Texture);
    Entity() = default;

    [[nodiscard]] double coord_x() const;

    [[nodiscard]] double coord_y() const;

    [[nodiscard]] double height() const;

    [[nodiscard]] double width() const;

    [[nodiscard]] double target_x() const;

    [[nodiscard]] double target_y() const;

    [[nodiscard]] int danger() const;
    virtual void draw();
    virtual void update();

    ///
    ///
};
class Living : public Entity {
protected:
    double speed = 0;
    double lastY = screenHeight;
    bool canJump = true, cont = true, isJumping = false;
    bool tookDamage = false;
    void moveX();
    void moveY();
public:
    Living(double x, double y, const Texture2D &Texture);
    explicit Living(const Texture2D &texture);
    Living() = default;
    [[nodiscard]] bool isAlive() const;
    virtual void moveToTarget(){}
    virtual void setLastY();
    virtual void collision(Entity &other, int directie);
};


class Player : public Living {
    bool gaveDamage = false;
public:
    Player(double x,  double y);
    Player();
    void handleInput();
   // void moveX();
    //void moveY();
    void update() override;
    void collision(Entity &other, int directie) override;
    void collision();
    void moveToTarget() override;
    //void moveToTarget() override;
   // void gravity() override;
  //  void setLastY() override;
};


class Enemy : public Living {
protected:
    bool change = false;
public:
    Enemy(double x, double y, const Texture2D &Texture);
    void incomingDamage() override;
};


class Turtle : public Enemy {
    static int isd;
    int local_id = ++isd;
public:
    Turtle(double x, double y);
    void collision(Entity &other, int directie) override;

    static void collision();
    void update() override;
    void moveToTarget() override;
};


//class Enemy : public
class Enviroment : public Entity
{
public:
    Enviroment(double x, double y);
    Enviroment();
};

#endif //ENTITATI_H
