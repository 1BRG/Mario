//
// Created by Gabriel on 4/16/2025.
//

#include "../include/Entities/Player.h"

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
    damage = 1;
    animations[IDLE] = AnimationManager::animations.get("mario_idle");
    animations[RUN] = AnimationManager::animations.get("mario_run");
    animations[JUMP] = AnimationManager::animations.get("mario_jump");
    animations[SKIDDING] = AnimationManager::animations.get("mario_skidding");
    sounds[JUMPPING] = ResourceAudio::audio.get("marioJump");
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
    if (isJumping) {
        bool ok;
        ok = true;
    }
}

void Player::setScore(std::shared_ptr<ScoreManager> Score) {
    score = Score;
}

void Player::update() {
    handleInput();
    moveX();
    moveY();
    if (targetY < coordY && coordY == lastY) {
        sounds[JUMPPING]->play();
    }
}

void Player::collision(Entity &other, const int direction) {
    if (auto coin = dynamic_cast<Coin *>(&other); coin != nullptr) {
        coin->collect();
        if (score) {
            score->addScore(2000);
        }
        return;
    }
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
        targetX = std::min(targetX, other.coord_x() - width() - 1), speed /= 2;
    else if (direction == -2)
        targetX = std::max(targetX, other.coord_x() + other.width() + 1), speed /= 2;

    if (other.danger() && direction != 1)
        tookDamage = true;
    //canUpdate = false;
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
    coordX = targetX;
    coordY = targetY;
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
