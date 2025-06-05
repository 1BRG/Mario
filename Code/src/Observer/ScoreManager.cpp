
//
// Created by Gabriel on 6/2/2025.
//

#include "../../include/Observer/ScoreManager.h"

// Increase score based on event type
void ScoreManager::onNotify(EventType event, std::shared_ptr<Entity> entity) {
    if (event == Question_hit) {
        score += 100;             // Points for hitting question block
    }
    if (event == Brick_break) {
        score += 50;              // Points for breaking brick
    }
    if (event == Coin_collected) {
        score += 1000;            // Points for collecting coin
    }
    if (event == PowerUp_collected) {
        score += 2000;            // Points for collecting power-up
    }
}

// Return current score value
int ScoreManager::getScore() const {
    return score;
}

// Add arbitrary points to score
void ScoreManager::addScore(int i) {
    score += i;
}
