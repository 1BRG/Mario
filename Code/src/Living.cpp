//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Living.h"

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