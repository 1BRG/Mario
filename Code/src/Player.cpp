//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Player.h"

Player::Player(const float x, const float y) : Living(x, y, MarioTexture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
    health = 1;
}

Player::Player() : Living(MarioTexture) {
    health = 1;
}

void Player::handleInput() {
    updateLeft = updateRight = false;
    updateTop = updateBottom = false;
    bool ok = false;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        speed -= DefaultSpeed * ProcentAlergare * dt, updateLeft = true;
        ok = true;
    }  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        speed += DefaultSpeed * ProcentAlergare * dt, updateRight = true;
        ok = true;
    } if (!ok) {
        if (speed != 0) {
            if (speed < 0)
                speed += DefaultSpeed * ProcentAlergare * dt, speed = min(speed, float(0.0)), updateLeft = updateRight = true;
            else speed -= DefaultSpeed * ProcentAlergare * dt, speed = max(speed, float(0.0)), updateRight = updateLeft = true;
        }
    }
    if (IsKeyDown(KEY_UP)) {
        bool ok;
        ok = true;
    }
    isJumping = (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) & canJump;
    updateTop = isJumping;
}

void Player::update() {
    handleInput();
    moveX();
    moveY();
}

void Player::collision(Entity &other, int directie) {
    if (directie == -2) {
        int mo;
        mo = 0;
    }
    if (directie == 1) {
        targetY = max(coordY, min(targetY, other.coord_y() - y));
            lastY = targetY;
         if (other.danger())
             other.incomingDamage(), gaveDamage = true;
    }
    else if (directie == -1 && targetY - coordY < 0) {
        targetY = max(coordY, max(targetY, other.coord_y() + other.height()));
        cont = false, cont = false, canJump = false;
    }
    else if (directie == 2 && targetX - coordX > 0)
        targetX = min(targetX, other.coord_x() - width());
    else if (targetX - coordX < 0)
        targetX = max(targetX, other.coord_x() + other.width());

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
    if (updateLeft) {
        coordX = targetX;
    }
    if (updateRight) {
        coordX = targetX;
    }
    if (updateBottom) {
        coordY = targetY;
    }
    if (updateTop) {
        coordY = targetY;
    }
    updateBottom = updateTop = false;
    updateLeft = updateRight = false;
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
