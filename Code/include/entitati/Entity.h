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
    float dt;
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
    Entity(double x, double y, const Texture2D &Texture);
    explicit Entity(const Texture2D &Texture);
    Entity() = default;
    [[nodiscard]] static double clamp(double x, double st, double dr);
    [[nodiscard]] double coord_x() const;

    [[nodiscard]] double coord_y() const;

    [[nodiscard]] double height() const;

    [[nodiscard]] double width() const;

    [[nodiscard]] double target_x() const;

    [[nodiscard]] double target_y() const;

    [[nodiscard]] int danger() const;
    virtual void draw();
    void deltaTime(float dt);
    virtual void update();
    void decreaseX(int dec);

    ///
    ///
};


//class Enemy : public
class Enviroment : public Entity
{
public:
    Enviroment(double x, double y);
    Enviroment();
};

#endif //ENTITATI_H
