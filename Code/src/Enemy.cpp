//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Enemy.h"

Enemy::Enemy(const float x, const float y, Animation *anim[3]) : Living(x, y, anim) {
    lastY = screenHeight;
    targetX = coordX, targetY = coordY;
}

void Enemy::incomingDamage() {
    tookDamage = true;
}
