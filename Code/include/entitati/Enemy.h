//
// Created by Gabriel on 4/16/2025.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "Living.h"


class Enemy : public Living {
protected:
    bool change = false;
public:
    Enemy(float x, float y, Animation* anim[3]);
    void incomingDamage() override;
};



#endif //ENEMY_H
