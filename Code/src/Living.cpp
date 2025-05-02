//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Living.h"

void Living::setLastY() {
    if (coordY >= lastY)
        lastY = screenHeight;
}

Living::Living(const float x, const float y, const Texture2D &texture) : Entity(x, y, texture) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

Living::Living(const Texture2D &texture) : Entity(texture) {
}

void Living::moveX() {
    speed = clamp(speed, -DefaultSpeed * 1.5, DefaultSpeed * 1.5);
    targetX += speed * dt;
}
bool Living::isAlive() const {
    return health;
}

void Living::moveY() {
    if (isJumping) {
        targetY -= Jump * dt;
        updateTop = true;
        if (targetY <= JumpMax)
            canJump = false;
    }
    else {
        if (targetY != lastY && cont == false)
            targetY += Jump * dt , canJump = false, updateBottom = true;
        else if (targetY != lastY && cont == true) {
            if (targetY > JumpMin && lastY != screenHeight)
                targetY -= Jump * dt, updateTop = true;
            else cont = false;
        }
        else canJump = true, cont = true;
    }
}

void Living::collision(Entity &other, int directie)
{}

bool Living::inCollision(const shared_ptr<Entity> &env, int a, int b) const {
    return CheckCollisionRecs(env->getRect(0, 0), getRect(a,  b));
}
/*
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
*/
bool Living::bottomCollision(const shared_ptr<Entity> &env) {
    if (inCollision(env, 0, 1) && detectCollisionSide(env, 0, 1) == "BOTTOM")
        return true;
    return false;
}

bool Living::topCollision(const shared_ptr<Entity> &env) {
    if (inCollision(env, 0, -1) && detectCollisionSide(env, 0, -1) == "TOP")
        return true;
    return false;
}

bool Living::leftCollision(const shared_ptr<Entity> &env) {
    if (inCollision(env, -1, 0) && detectCollisionSide(env, -1, 0) == "LEFT")
        return true;
    return false;
}

bool Living::rightCollision(const shared_ptr<Entity> &env) {
    if (inCollision(env, 1, 0) && detectCollisionSide(env, 1, 0) == "RIGHT")
        return true;
    return false;
}
