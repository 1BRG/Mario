//
// Created by Gabriel on 4/1/2025.
//
#include <iostream>
#include "../include/entitati/Entitati.h"

#include <bits/stl_algo.h>


Entity::Entity(const double x, const double y, const Texture2D &Texture) : coordX(x), coordY(y), texture(Texture) {
    this->x =  Texture.width;
    this->y =  Texture.height;
    targetX = coordX;
    targetY = coordY;
}

Entity::Entity(const Texture2D &Texture) : texture(Texture) {
    this->x =  Texture.width;
    this->y =  Texture.height;
};

[[nodiscard]] double Entity::coord_x() const {
    return coordX;
}

[[nodiscard]] double Entity::coord_y() const {
    return coordY;
}

[[nodiscard]] double Entity::width() const {
    return x;
}

[[nodiscard]] double Entity::height() const {
    return y;
}

[[nodiscard]] double Entity::target_x() const {
    return targetX;
}

[[nodiscard]] double Entity::target_y() const {
    return targetY;
}

void Entity::draw() {
    DrawTexture(texture, floor(coordX), floor(coordY), WHITE);
}

void Entity::update() {
}

int Entity::danger() const {
    return damage;
};
void Entity::collision(Entity &other, int direction) {
}











Player::Player(const double x, const double y) : Living(x, y, MarioTexture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
    health = 1;
}

Player::Player() : Living(MarioTexture) {
    health = 1;
}

void Player::handleInput() {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        speed -= DefaultSpeed * ProcentAlergare;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        speed += DefaultSpeed * ProcentAlergare;
    } else {
        if (speed != 0) {
            if (speed < 0)
                speed += DefaultSpeed * ProcentAlergare, speed = min(speed, 0.0);
            else speed -= DefaultSpeed * ProcentAlergare, speed = max(speed, 0.0);
        }
    }
    isJumping = (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) & canJump;
}

void Player::update() {
    handleInput();
    moveX();
    moveY();
}

void Player::collision(Entity &other, int directie) {
    if (directie == 1) {
        targetY = min(targetY, other.coord_y() - y - 1);
            lastY = targetY;
         if (other.danger()) other.incomingDamage(), gaveDamage = true;
    }
    else if (directie == -1) {
        targetY = max(targetY, other.coord_y() + other.height() + 1);
        cont = false, cont = false, canJump = false;
    }
    else if (directie == 2) updateRight = false;
    else updateLeft = false;
    if (other.danger() && directie != 1)
        tookDamage = true;
    //canUpdate = false;
}
void Player::collision() {
}

/*
void Player::gravity() {
    if (coordY == lastY)
        canJump = true;
     if (!canJump) {
         targetY = coordY + 1;
     }
}
*/
void Player::moveToTarget() {
   // cout << "ba";
    if (updateLeft && targetX - coordX <= 0) {
        coordX = targetX;
    }
    if (updateRight && targetX - coordX >= 0) {
        coordX = targetX;
    }
    if (updateBottom && targetY - coordY >= 0) {
        coordY = targetY;
    }
    if (updateTop && targetY - coordY <= 0) {
        coordY = targetY;
    }

    updateBottom = updateTop = true;
    updateLeft = updateRight = true;
    // canUpdate = true;
    targetX = coordX;
    targetY = coordY;
    if (tookDamage) {
        health --;
    }
    if (tookDamage || gaveDamage){
        // cont = true;
        canJump = false;
        cont = true;
        coordY = targetY = coordY - 5 * Jump;
    }
    gaveDamage = false;
    tookDamage = false;
}

void Living::setLastY() {
    if (coordY >= lastY)
    lastY = screenHeight;
}

Living::Living(const double x, const double y, const Texture2D &texture) : Entity(x, y, texture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

Living::Living(const Texture2D &texture) : Entity(texture) {
}

void Living::moveX() {
    speed = clamp(speed, -DefaultSpeed * 1.5, DefaultSpeed * 1.5);
    targetX += speed;
}
bool Living::isAlive() const {
    return health;
}

void Living::moveY() {
    if (isJumping) {
        targetY -= Jump;
        if (targetY <= JumpMax)
            canJump = false;
    } else {
        if (targetY != lastY && cont == false)
            targetY += Jump, canJump = false;
        else if (targetY != lastY && cont == true) {
            if (targetY > JumpMin && lastY != screenHeight)
                targetY -= Jump;
            else cont = false;
        } else canJump = true, cont = true;
    }
}

void Living::collision(Entity &other, int directie)
{}
int Turtle::isd = 0;
Enemy::Enemy(const double x, const double y, const Texture2D &texture) : Living(x, y, texture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}
void Enemy::incomingDamage() {
    tookDamage = true;
}


Turtle::Turtle(const double x, const double y) : Enemy(x, y, TurtleTexture) {
    health = 2;
    damage = 1;
    speed = DefaultSpeed;
}

void Turtle::update() {
    moveX();
    moveY();
}

void Turtle::collision(Entity &other, int directie) {

    if (directie == 1) {
        lastY = coordY;
        updateBottom = false;
        targetY = min(targetY, other.coord_y() - y - 1);
    }
    else if (directie == -1) {
        cont = false;
        updateTop = false;
        cont = false;
        canJump = false;
    }
    else if (directie == 2 && targetX - coordX > 0) {
        targetX = min(targetX, other.coord_x() - x - 1), change = true;
    }
    else if (directie == -2 && targetX - coordX < 0) {
        targetX = max(targetX, other.coord_x() + other.width() + 1), change = true;
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
        texture = FuriousTurtleTexture;
        x = texture.width;
        y = texture.height;
        damage ++;
        speed *= 2;
    }
    tookDamage = false;
    targetY = coordY;
    targetX = coordX;
}


Enviroment::Enviroment(const double x, const double y) : Entity(x, y, BrickTexture) {
}

Enviroment::Enviroment() {
    texture = BrickTexture;
}




