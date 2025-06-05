
//
// Created by Gabriel on 6/2/2025.
//

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "IObserver.h"

// Manages player score by observing game events
class ScoreManager : public IObserver {
    int score{0}; // Current accumulated score

public:
    ScoreManager() = default;
    ~ScoreManager() override = default;

    // Handle events to update score
    void onNotify(EventType event, std::shared_ptr<Entity> entity) override;

    // Retrieve current score
    int getScore() const;

    // Manually add to score
    void addScore(int i);
};

#endif //SCOREMANAGER_H
