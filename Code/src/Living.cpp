//
// Created by Gabriel on 4/16/2025.
//

#include "../include/Entities/Living.h"

#include <iostream>

void Living::setLastY() {
    if (coordY >= lastY)
        lastY = screenHeight;
}

Living::Living(const float x, const float y) : Entity(x, y) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

void Living::moveX() {
    speed = clamp(double(speed), -DefaultSpeed * 1.5, DefaultSpeed * 1.5);
    velocity.x = speed * dt;
    targetX += speed * dt;
}

void Living::draw(float cameraX) {
    animations[state]->Draw({coordX - cameraX, coordY}, WHITE, dt, speed < 0);
    x = animations[state]->width();
    y = animations[state]->height();
}


void Living::moveY() {
    if (isJumping) {
        state = JUMP;
        targetY -= Jump * dt;
        velocity.y -= Jump * dt;
        updateTop = true;
        if (targetY <= JumpMax)
            canJump = false;
    } else {
        if (targetY != lastY && cont == false) {
            state = JUMP;
            targetY += Jump * dt;
            canJump = false;
            updateBottom = true;
            velocity.y += Jump * dt;
        } else if (targetY != lastY && cont == true) {
            if (targetY > JumpMin && lastY != screenHeight) {
                state = JUMP;
                targetY -= Jump * dt;
                updateTop = true;
                velocity.y -= Jump * dt;
            } else cont = false;
        } else canJump = true, cont = true, velocity.y = 0;
    }
}

void Living::collision(Entity &other, int direction) {
    //bs
    int ok = other.danger();
    if (direction == 1) {
        ok &= 1;
        direction += ok;
    }
    other.decreaseX(direction);
    other.decreaseX(-direction);
}

void Living::print() const {
    Entity::print();
    std::cout << "Speed : " << speed << std::endl << std::endl;
}


bool Living::inCollision(const std::shared_ptr<Entity> &env, int a, int b) const {
    return CheckCollisionRecs(env->getRect(0, 0), getRect(a, b));
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
bool Living::bottomCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, 0, 2) && detectCollisionSide(env, 0, 1) == "BOTTOM")
        return true;
    return false;
}

bool Living::topCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, 0, -2) && detectCollisionSide(env, 0, -1) == "TOP")
        return true;
    return false;
}

bool Living::leftCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, -2, 0) && detectCollisionSide(env, -1, 0) == "LEFT") {
        bool ok;
        ok = true;
    }
    if (inCollision(env, -2, 0) && detectCollisionSide(env, -1, 0) == "LEFT")
        return true;
    return false;
}

bool Living::rightCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, 2, 0) && detectCollisionSide(env, 1, 0) == "RIGHT")
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &os, const Living &living) {
    living.print();
    return os;
}
