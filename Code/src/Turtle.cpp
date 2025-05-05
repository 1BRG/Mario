//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Turtle.h"

int Turtle::isd = 0;



Turtle::Turtle(const float x, const float y) : Enemy(x, y, TurtleTexture) {
    health = 2;
    damage = 1;
    speed = DefaultSpeed;
}
Turtle::Turtle(const float x, const float y, int a) : Enemy(x, y, FuriousTurtleTexture) {
    damage = 2;
    speed = 2 * DefaultSpeed;
    health = a;
}
Turtle *Turtle::clone() const {
        return new Turtle(*this);
}

Turtle & Turtle::operator=(const Turtle &other) {
    if (this == &other)
        return *this;
    UnloadTexture(texture);
    Enemy::operator=(other);
    damage = other.damage;
    speed  = other.speed;
    health = other.health;

    texture = LoadTexture(other.texturePath.c_str());
    if (texture.id == 0)
        throw TextureException(texturePath);
    x = texture.width;
    y = texture.height;
    return *this;
}

void Turtle::update() {
    moveX();
    moveY();
}

void Turtle::collision(Entity &other, int directie) {
    if (directie == 1) {
      //  updateBottom = false;
        targetY = std::min(targetY, other.coord_y() - y);
        lastY = targetY;
    }
    else if (directie == -1) {
        cont = false;
    //    updateTop = false;
        cont = false;
        canJump = false;
    }
    else if (directie == 2) {
        targetX = std::min(targetX, other.coord_x() - x), change = true;
    }
    else if (directie == -2) {
        targetX = std::max(targetX, other.coord_x() + other.width()), change = true;
    }
    if (other.danger() > 1)
        tookDamage = true;
}

void Turtle::collision(){}

void Turtle::moveToTarget() {
    if (change) speed *= -1;
    else coordX = targetX, coordY = targetY;
    change = false;
    if (tookDamage) {
        health --;
        *this = Turtle(coordX, coordY, health);
    }
    else {
        tookDamage = false;
        targetY = coordY;
        targetX = coordX;
    }
}