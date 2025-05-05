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

    Turtle(float x, float y, int i);

    void collision(Entity &other, int directie) override;

    static void collision();
    void update() override;
    void moveToTarget() override;
    Turtle * clone() const override;
    Turtle& operator=(const Turtle& other);
    Turtle(const Turtle& other) = default;
};



#endif //TURTLE_H
