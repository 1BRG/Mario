//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Player.h"

#include <iostream>
std::string Player::MarioIDLE = "../Texture/all/Mario.png";
std::string Player::MarioRUN = "../Texture/all/MarioRun.png";
std::string Player::MarioJUMP = "../Texture/all/MarioJumping.png";
std::string Player::MarioSKIDDING = "../Texture/all/MarioSkidding.png";

Player::Player(const float x, const float y)
    : Living(x, y) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
    health = 1;
    animations[IDLE] = AnimationManager::animations.load(
        "mario_idle", MarioIDLE, 1, 6);
    animations[RUN] = AnimationManager::animations.load(
        "mario_run", MarioRUN, 3, 12);
    animations[JUMP] = AnimationManager::animations.load(
        "mario_jump", MarioJUMP, 1, 4);
    animations[SKIDDING] = AnimationManager::animations.load(
        "mario_skidding", MarioSKIDDING, 1, 1);
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
    state = RUN;
}


void Player::handleInput() {
    state = IDLE;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        if (speed > 0)
            state = SKIDDING;
        else state = RUN;
        speed -= DefaultSpeed * ProcentAlergare * dt;
        updateLeft = true;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        if (speed < 0)
            state = SKIDDING;
        else state = RUN;
        speed += DefaultSpeed * ProcentAlergare * dt;
    } else {
        if (speed != 0) {
            state = RUN;
            if (speed < 0) {
                speed += DefaultSpeed * ProcentAlergare * dt;
                speed = std::min(speed, static_cast<float>(0.0));
            } else {
                speed -= DefaultSpeed * ProcentAlergare * dt;
                speed = std::max(speed, static_cast<float>(0.0));
            }
        }
    }
    isJumping = (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) & canJump;
}

void Player::update() {
    handleInput();
    moveX();
    moveY();
}

void Player::collision(Entity &other, const int direction) {
    // std::cout << health << std::endl;
    if (direction == 1 && targetY - coordY >= 0) {
        targetY = std::min(targetY, other.coord_y() - y);
        lastY = targetY;
        if (other.danger())
            other.incomingDamage(), gaveDamage = true;
    } else if (direction == -1 && targetY - coordY <= 0) {
        targetY = std::max(targetY, other.coord_y() + other.height());
        cont = false, cont = false, canJump = false;
    } else if (direction == 2)
        targetX = std::min(targetX, other.coord_x() - width());
    else if (direction == -2)
        targetX = std::max(targetX, other.coord_x() + other.width());

    if (other.danger() && direction != 1)
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
Player *Player::clone() const {
    return new Player(*this);
}

void Player::moveToTarget() {
    // cout << "ba";

    if (updateLeft && targetX - coordX <= 0) {
        coordX = targetX;
    }
    if (updateRight && targetX - coordX >= 0) {
        coordX = targetX;
    }
    if (updateBottom && targetY - coordY > 0) {
        coordY = targetY;
    }
    if (updateTop && targetY - coordY < 0) {
        coordY = targetY;
    }
    updateBottom = updateTop = true;
    updateLeft = updateRight = true;
    // canUpdate = true;
    targetX = coordX;
    targetY = coordY;
    if (tookDamage) {
        health--;
    }
    if (tookDamage || gaveDamage) {
        // cont = true;
        canJump = false;
        cont = true;
        coordY = targetY = coordY - 5 * Jump * dt;
    }
    gaveDamage = false;
    tookDamage = false;
}
