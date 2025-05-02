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

class Entity
{
protected:
    float dt;
    float coordX = 0, coordY = 0, x = 0, y = 0;
    float targetX = 0, targetY = 0;
    int health = 1;
    bool moving = true;
    int damage = 0;
    bool updateLeft = true, updateRight = true, updateTop = true, updateBottom = true;
    Texture2D texture;
public:

    virtual ~Entity() = default;
    virtual void incomingDamage() {}
    virtual void collision(Entity &other, int direction);

    [[nodiscard]] std::string detectCollisionSide(const std::shared_ptr<Entity> &env, int a, int b) const;

    Entity(float x, float y, const Texture2D &Texture);
    explicit Entity(const Texture2D &Texture);
    Entity() = default;
    [[nodiscard]] static float clamp(float x, float st, float dr);
    [[nodiscard]] float coord_x() const;

    [[nodiscard]] float coord_y() const;

    [[nodiscard]] float height() const;

    [[nodiscard]] float width() const;

    [[nodiscard]] float target_x() const;

    [[nodiscard]] float target_y() const;

    [[nodiscard]] int danger() const;
    virtual void draw(int cameraX);
    void deltaTime(float dt);
    virtual void update();
    void decreaseX(int dec);
    [[nodiscard]] Rectangle getRect(int a, int b) const;
    ///
    ///
};


//class Enemy : public
class Enviroment : public Entity
{
public:
    Enviroment(float x, float y);
    Enviroment();
};

#endif //ENTITATI_H
