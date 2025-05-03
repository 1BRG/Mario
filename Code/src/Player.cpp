//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Player.h"

#include <iostream>
Player::Player(const float x, const float y) : Living(x, y, MarioTexture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
    health = 1;
}

Player::Player() : Living(MarioTexture) {
    health = 1;
}

void Player::handleInput() {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        speed -= DefaultSpeed * ProcentAlergare * dt, updateLeft = true;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        speed += DefaultSpeed * ProcentAlergare * dt;
    } else {
        if (speed != 0) {
            if (speed < 0)
                speed += DefaultSpeed * ProcentAlergare * dt, speed = std::min(speed, float(0.0));
            else speed -= DefaultSpeed * ProcentAlergare * dt, speed = std::max(speed, float(0.0));
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
   // std::cout << health << std::endl;
    if (directie == 1) {
        targetY = std::min(targetY, other.coord_y() - y);
        lastY = targetY;
         if (other.danger())
             other.incomingDamage(), gaveDamage = true;
    }
    else if (directie == -1 && targetY - coordY < 0) {
        targetY = std::max(targetY, other.coord_y() + other.height());
        cont = false, cont = false, canJump = false;
    }
    else if (directie == 2)
        targetX = std::min(targetX, other.coord_x() - width());
    else
        targetX = std::max(targetX, other.coord_x() + other.width());

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
        coordY = targetY = coordY - 5 * Jump * dt;
    }
    gaveDamage = false;
    tookDamage = false;
}
