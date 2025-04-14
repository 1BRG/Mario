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
    return coordX;
}

[[nodiscard]] double Entity::target_y() const {
    return coordY;
}

void Entity::draw() {
    DrawTexture(texture, floor(coordX), floor(coordY), WHITE);
}

void Entity::update() {
}

void Entity::collision(Entity &other, int directie) {

}
bool Entity::danger() const {
    return damage;
};

void Entity::moveToTarget() {
    if (updateLeft && updateRight) {
        coordX = targetX;
    }
    if (updateBottom && updateTop) {
        coordY = targetY;
    }
    updateBottom = updateTop = true;
    updateLeft = updateRight = true;
   // canUpdate = true;
    targetX = coordX;
    targetY = coordY;
}


Player::Player(const double x, const double y) : Entity(x, y, MarioTexture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

Player::Player() : Entity(MarioTexture) {
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

void Player::moveX() {
    speed = clamp(speed, -DefaultSpeed * 1.5, DefaultSpeed * 1.5);
    targetX += speed;
}

void Player::moveY() {
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

void Player::update() {
    handleInput();
    moveX();
    moveY();
}

void Player::collision(Entity &other, int directie) {
    if (directie == 1)
        lastY = coordY, updateBottom = false, targetY = min(targetY, other.coord_y() - y - 1);
    else if (directie == -1)
        cont = false, updateTop = false, cont = false, canJump = false;
    else updateLeft = updateRight = false;
    if (other.danger())
        health --;
    //canUpdate = false;
}
void Player::collision() {
}

void Player::gravity() {
    if (coordY == lastY)
        canJump = true;
     if (!canJump) {
         targetY = coordY + 1;
     }
}

void Player::moveToTarget() {
   // cout << "ba";
    if (updateLeft && updateRight) {
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
}

void Player::setLastY() {
    if (coordY == lastY)
    lastY = screenHeight;
}

Enviroment::Enviroment(const double x, const double y) : Entity(x, y, BrickTexture) {
}

Enviroment::Enviroment() {
    texture = BrickTexture;
}




