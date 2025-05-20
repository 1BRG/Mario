//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Enemy.h"

Enemy::Enemy(const float x, const float y) : Living(x, y) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

void Enemy::incomingDamage() {
    tookDamage = true;
}
