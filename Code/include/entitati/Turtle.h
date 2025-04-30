//
// Created by Gabriel on 4/16/2025.
//

#ifndef TURTLE_H
#define TURTLE_H
#include "Enemy.h"


class Turtle : public Enemy {
    static int isd;
    int local_id = ++isd;
public:
    Turtle(float x, float y);
    void collision(Entity &other, int directie) override;

    static void collision();
    void update() override;
    void moveToTarget() override;
};



#endif //TURTLE_H
