//
// Created by Gabriel on 4/16/2025.
//

#ifndef ENEMY_H
#define ENEMY_H
#include "Living.h"

// Enemy entity with specific damage handling
class Enemy : public Living {
protected:
    bool change{false};     // Flag for changing behavior (e.g., direction)

public:
    Enemy(float x, float y);            // Constructor with initial position

    void incomingDamage() override;      // Handle being damaged
};

#endif //ENEMY_H
