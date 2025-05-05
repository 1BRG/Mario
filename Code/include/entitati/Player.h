//
// Created by Gabriel on 4/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Living.h"


class Player : public Living {
    bool gaveDamage = false;
public:
    Player(float x,  float y);
    Player();
    void handleInput();
    // void moveX();
    //void moveY();
    void update() override;
    void collision(Entity &other, int directie) override;

    static void collision();
    void moveToTarget() override;
    Player * clone() const override;
    //void moveToTarget() override;
    // void gravity() override;
    //  void setLastY() override;
};




#endif //PLAYER_H
