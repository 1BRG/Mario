
//
// Created by Gabriel on 4/16/2025.
//

#include "../include/Entities/Player.h"
#include <iostream>

// Animation file paths initialized statically
std::string Player::MarioIDLE = "../Texture/all/Mario.png";
std::string Player::MarioRUN = "../Texture/all/MarioRun.png";
std::string Player::MarioJUMP = "../Texture/all/MarioJumping.png";
std::string Player::MarioSKIDDING = "../Texture/all/MarioSkidding.png";

// Set up player animations, sounds, and stats
Player::Player(const float x, const float y)
    : Living(x, y) {
    lastY = screenHeight;            // Reset last Y-coordinate
    targetX = coordX, targetY = coordY; // Initialize movement targets
    health = 1;                      // Set initial health
    damage = 1;                      // Set damage dealt on collision
    animations[IDLE] = AnimationManager::animations.get("mario_idle");
    animations[RUN] = AnimationManager::animations.get("mario_run");
    animations[JUMP] = AnimationManager::animations.get("mario_jump");
    animations[SKIDDING] = AnimationManager::animations.get("mario_skidding");
    sounds[JUMPPING] = ResourceAudio::audio.get("marioJump");
    this->x = animations[IDLE]->width(); // Set hitbox width
    this->y = animations[IDLE]->height(); // Set hitbox height
    state = RUN;                      // Default state
}

// Read user input to adjust speed and jump flag
void Player::handleInput() {
    state = IDLE;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        if (speed > 0)
            state = SKIDDING;       // Changing direction skid
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
            // Decelerate to zero
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
        bool ok; ok = true;          // Placeholder for jump trigger
    }
}

// Assign score manager observer
void Player::setScore(const std::shared_ptr<ScoreManager> &Score) {
    score = Score;
}

// Update movement, physics, and play jump sound when leaving ground
void Player::update() {
    handleInput();
    moveX();
    moveY();
    if (targetY < coordY && coordY == lastY) {
        sounds[JUMPPING]->play();    // Play jump sound on takeoff
    }
}

// Collision handling: coins, platforms, enemies
void Player::collision(Entity &other, const int direction) {
    if (auto coin = dynamic_cast<Coin *>(&other); coin != nullptr) {
        coin->collect();             // Collect coin
        if (score) {
            score->addScore(2000);   // Update score
        }
        return;
    }
    if (direction == 1 && targetY - coordY >= 0) {
        targetY = std::min(targetY, other.coord_y() - y); // Land on top
        lastY = targetY;
        if (other.danger())
            other.incomingDamage(), gaveDamage = true; // Damage enemy
    } else if (direction == -1 && targetY - coordY <= 0) {
        targetY = std::max(targetY, other.coord_y() + other.height()); // Hit head
        cont = false, canJump = false;
    } else if (direction == 2)
        targetX = std::min(targetX, other.coord_x() - width() - 1), speed /= 2; // Hit right wall
    else if (direction == -2)
        targetX = std::max(targetX, other.coord_x() + other.width() + 1), speed /= 2; // Hit left wall

    if (other.danger() && direction != 1)
        tookDamage = true;           // Take damage if hitting dangerous side
}

// Clone object for prototypes
Player *Player::clone() const {
    return new Player(*this);
}

// Apply movement deltas and handle damage bounce
void Player::moveToTarget() {
    coordX = targetX;
    coordY = targetY;
    if (updateLeft && targetX - coordX <= 0) coordX = targetX;
    if (updateRight && targetX - coordX >= 0) coordX = targetX;
    if (updateBottom && targetY - coordY > 0) coordY = targetY;
    if (updateTop && targetY - coordY < 0) coordY = targetY;
    updateBottom = updateTop = true;
    updateLeft = updateRight = true;
    targetX = coordX;
    targetY = coordY;
    if (tookDamage) {
        health--;                    // Decrease health on hit
    }
    if (tookDamage || gaveDamage) {
        canJump = false;
        cont = true;
        coordY = targetY = coordY - 5 * Jump * dt; // Bounce effect
    }
    gaveDamage = false;
    tookDamage = false;
}
