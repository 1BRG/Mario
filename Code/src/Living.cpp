
//
// Created by Gabriel on 4/16/2025.
//

#include "../include/Entities/Living.h"
#include <iostream>

// Reset lastY when entity is on or above previous Y
void Living::setLastY() {
    if (coordY >= lastY)
        lastY = screenHeight;
}

// Initialize living entity position and lastY
Living::Living(const float x, const float y) : Entity(x, y) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

// Update horizontal position based on speed and delta time
void Living::moveX() {
    speed = clamp(double(speed), -DefaultSpeed * 1.5, DefaultSpeed * 1.5);
    velocity.x = speed * dt;
    targetX += speed * dt;
}

// Draw entity and flip sprite when moving left
void Living::draw(float cameraX) {
    animations[state]->Draw({coordX - cameraX, coordY}, WHITE, dt, speed < 0);
    x = animations[state]->width();
    y = animations[state]->height();
}

// Apply gravity or jumping physics each frame
void Living::moveY() {
    if (isJumping) {
        state = JUMP;
        targetY -= Jump * dt;
        velocity.y -= Jump * dt;
        updateTop = true;
        if (targetY <= JumpMax)
            canJump = false; // Stop upward movement at max height
    } else {
        if (targetY != lastY && cont == false) {
            state = JUMP;
            targetY += Jump * dt; // Falling down
            canJump = false;
            updateBottom = true;
            velocity.y += Jump * dt;
        } else if (targetY != lastY && cont == true) {
            if (targetY > JumpMin && lastY != screenHeight) {
                state = JUMP;
                targetY -= Jump * dt; // Continue upward if within bounds
                updateTop = true;
                velocity.y -= Jump * dt;
            } else cont = false; // Switch to falling
        } else canJump = true, cont = true, velocity.y = 0; // On ground
    }
}

// Default collision response: adjust other entity's X based on direction
void Living::collision(Entity &other, int direction) {
    int ok = other.danger(); // Get damage flag
    if (direction == 1) {
        ok &= 1;
        direction += ok;
    }
    other.decreaseX(direction);
    other.decreaseX(-direction);
}

// Print health and speed for debugging
void Living::print() const {
    Entity::print();
    std::cout << "Speed : " << speed << std::endl << std::endl;
}

// Check AABB collision with offset
bool Living::inCollision(const std::shared_ptr<Entity> &env, int a, int b) const {
    return CheckCollisionRecs(env->getRect(0, 0), getRect(a, b));
}

// Check collision from below
bool Living::bottomCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, 0, 2) && detectCollisionSide(env, 0, 1) == "BOTTOM")
        return true;
    return false;
}

// Check collision from above
bool Living::topCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, 0, -2) && detectCollisionSide(env, 0, -1) == "TOP")
        return true;
    return false;
}

// Check collision from left
bool Living::leftCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, -2, 0) && detectCollisionSide(env, -1, 0) == "LEFT") {
        bool ok;
        ok = true;
    }
    if (inCollision(env, -2, 0) && detectCollisionSide(env, -1, 0) == "LEFT")
        return true;
    return false;
}

// Check collision from right
bool Living::rightCollision(const std::shared_ptr<Entity> &env) const {
    if (inCollision(env, 2, 0) && detectCollisionSide(env, 1, 0) == "RIGHT")
        return true;
    return false;
}

// Stream insertion calls print()
std::ostream &operator<<(std::ostream &os, const Living &living) {
    living.print();
    return os;
}
