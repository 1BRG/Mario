
//
// Created by Gabriel on 4/16/2025.
//

#include "../include/Entities/Enemy.h"

// Initialize enemy at given coordinates
Enemy::Enemy(const float x, const float y) : Living(x, y) {
    lastY = screenHeight;                // Reset lastY for jump logic
    targetX = coordX, targetY = coordY;  // Initialize movement targets
}

// Mark that the enemy has taken damage this frame
void Enemy::incomingDamage() {
    tookDamage = true;
}