//
// Created by Gabriel on 6/2/2025.
//

#ifndef COIN_H
#define COIN_H

#include "Entity.h"
#include "../../include/Template/ResourceAnimation.h"
#include "../../include/Template/ResourceAudio.h"
#include "../Entities/Player.h"
#include <iostream>
#include "../observer/ISubject.h"

// Collectible coin that plays sound on pickup and notifies state
class Coin : public Entity {
    bool collected{false};  // Flag if coin has been picked up

public:
    Coin(float x, float y);        // Constructor sets up animation and sound

    ~Coin() override = default;    // Default destructor

    bool isCollected() const;      // Check if already collected

    void collect();                // Mark as collected and play sound

    void collision(Entity &other, int direction) override; // Pickup on player collision

    [[nodiscard]] Coin *clone() const override; // Clone coin for spawning
};

#endif //COIN_H