

//
// Created by Gabriel on 6/2/2025.
//

#include "../include/Entities/Coin.h"

// Initialize coin animation, sound, and hitbox
Coin::Coin(const float x, const float y) : Entity(x, y) {
    animations[IDLE] = AnimationManager::animations.get("coin_idle");
    ResourceAudio::audio.get("coinSound"); // Preload sound effect
    state = IDLE;                  // Set idle animation
    health = 1;                    // Alive until collected
    this->x = animations[IDLE]->width();   // Set width
    this->y = animations[IDLE]->height();  // Set height
}

// Return collected state
bool Coin::isCollected() const {
    return collected;
}

// Handle coin pickup: disable and play sound once
void Coin::collect() {
    if (collected) return;        // Prevent multiple pickups
    collected = true;
    health = 0;                   // Mark as inactive
    ResourceAudio::audio.get("coinSound")->play(); // Play pickup sound
}

// Trigger collect when player collides
void Coin::collision(Entity &other, int direction) {
    if (dynamic_cast<Player *>(&other) != nullptr && !collected) {
        collect();                 // Player collects coin
    }
}

// Clone for prototype-based spawning
Coin *Coin::clone() const {
    return new Coin(*this);
}
