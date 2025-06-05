

//
// Created by Gabriel on 4/16/2025.
//

#include "../include/Entities/Turtle.h"
#include <iostream>
#include "../include/Entities/Coin.h"

int Turtle::isd = 0;                 // Initialize static ID counter

std::string Turtle::TurtleRUN = "../Texture/all/TurtleRun.png";
std::string Turtle::FuriousRUN = "../Texture/all/FuriousRunFixed.png";

// Set up turtle animations, stats, and audio
Turtle::Turtle(const float x, const float y) : Enemy(x, y) {
    animations[IDLE] = AnimationManager::animations.get("turtle_idle");
    animations[JUMP] = AnimationManager::animations.get("turtle_jump");
    animations[RUN] = AnimationManager::animations.get("turtle_run");
    sounds[DIE] = ResourceAudio::audio.get("kickKill");
    health = 2;                      // Two hits to enraged state
    damage = 1;                      // Damage dealt before enraged
    state = RUN;                     // Default state on spawn
    this->x = animations[IDLE]->width();  // Hitbox dimensions
    this->y = animations[IDLE]->height();
    speed = DefaultSpeed;            // Movement speed
}

// Clone turtle for duplication
Turtle *Turtle::clone() const {
    return new Turtle(*this);
}

// Copy assignment loads texture and stats, throws on failure
Turtle &Turtle::operator=(const Turtle &other) {
    if (this == &other)
        return *this;
    UnloadTexture(texture);
    Enemy::operator=(other);
    damage = other.damage;
    speed = other.speed;
    health = other.health;

    texture = LoadTexture(other.texturePath.c_str());
    if (texture.id == 0)
        throw TextureException(texturePath);
    x = texture.width;
    y = texture.height;
    return *this;
}

// Update horizontal and vertical motion
void Turtle::update() {
    moveX();                         // Walk
    moveY();                         // Gravity/jump physics
}

// Handle collisions: ignore coins, bounce on death blow, reverse on walls
void Turtle::collision(Entity &other, int direction) {
    if (auto coin = dynamic_cast<Coin *>(&other); coin != nullptr) {
        return;                       // Skip coin collisions
    }
    if (direction == 1) {
        targetY = std::min(targetY, other.coord_y() - y); // Land
        lastY = targetY;
        state = RUN;                   // Resume running
    } else if (direction == -1) {
        cont = false;                  // Hit head, start falling
        canJump = false;
    } else if (direction == 2) {
        targetX = std::min(targetX, other.coord_x() - x - 1);
        change = true;                 // Reverse direction on right wall
    } else if (direction == -2) {
        targetX = std::max(targetX, other.coord_x() + other.width() + 1);
        change = true;                 // Reverse on left wall
    }
    if (other.danger() > 1)
        tookDamage = true;            // Enter enraged state if hit hard
}

// Apply movement and manage enraged behavior
void Turtle::moveToTarget() {
    if (change) speed *= -1;         // Reverse when flagged
    coordX = targetX, coordY = targetY;
    change = false;
    if (tookDamage) {
        health = std::max(health - 1, 0); // Decrement health
        try {
            auto furiousAnim = AnimationManager::animations.get("furiousRun");
            animations[RUN] = furiousAnim; // Switch to enraged animation
            animations[JUMP] = animations[IDLE] = furiousAnim;
        } catch (TextureException &ex) {
            std::cout << ex.what() << std::endl;
            exit(0);
        }
        sounds[DIE]->play();          // Play enraged sound
        damage = 2;                   // Increased damage
        speed *= 3;                   // Speed boost
        tookDamage = false;           // Reset flag
    } else {
        tookDamage = false;
        targetY = coordY;            // Reset targets when normal
        targetX = coordX;
    }
}
