//
// Created by Gabriel on 4/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Living.h"

#include "Coin.h"
#include "../Observer/ScoreManager.h"

class Player : public Living {
    static std::string MarioIDLE;
    static std::string MarioRUN;
    static std::string MarioJUMP;
    static std::string MarioSKIDDING;
    bool gaveDamage{false};
    std::shared_ptr<ScoreManager> score;

public:
    Player(float x, float y);

    Player() = default;

    void handleInput();

    void setScore(std::shared_ptr<ScoreManager> Score);

    // void moveX();
    //void moveY();
    void update() override;

    void collision(Entity &other, int direction) override;


    void moveToTarget() override;

    [[nodiscard]] Player *clone() const override;

    Player(const Player &other) = default;

    //void moveToTarget() override;
    // void gravity() override;
    //  void setLastY() override;
};


#endif //PLAYER_H
