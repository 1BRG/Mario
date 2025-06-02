//
// Created by Gabriel on 6/2/2025.
//

#include "../../include/Observer/ScoreManager.h"

void ScoreManager::onNotify(EventType event, std::shared_ptr<Entity> entity) {
    if (event == Question_hit) {
        score += 100;
    }
    if (event == Brick_break) {
        score += 50;
    }
    if (event == Coin_collected) {
        score += 1000;
    }
    if (event == PowerUp_collected) {
        score += 2000;
    }
}

int ScoreManager::getScore() {
    return score;
}

void ScoreManager::addScore(int i) {
    score += i;
}
