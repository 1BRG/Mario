//
// Created by Gabriel on 6/2/2025.
//

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "IObserver.h"

class ScoreManager : public IObserver {
    int score{0};

public:
    ScoreManager() = default;

    ~ScoreManager() override = default;

    void onNotify(EventType event, std::shared_ptr<Entity> entity) override;

    int getScore();

    void addScore(int i);
};


#endif //SCOREMANAGER_H
