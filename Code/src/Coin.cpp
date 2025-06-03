//
// Created by Gabriel on 6/2/2025.
//

#include "../include/Entities/Coin.h"

Coin::Coin(const float x, const float y) : Entity(x, y) {
    animations[IDLE] = AnimationManager::animations.get("coin_idle");
    ResourceAudio::audio.get("coinSound");
    state = IDLE;
    health = 1;
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::collect() {
    if (collected) return;
    collected = true;
    health = 0;
    ResourceAudio::audio.get("coinSound")->play();
}

void Coin::collision(Entity &other, int direction) {
    if (dynamic_cast<Player *>(&other) != nullptr && !collected) {
        collect();
    }
}

Coin *Coin::clone() const {
    return new Coin(*this);
}
