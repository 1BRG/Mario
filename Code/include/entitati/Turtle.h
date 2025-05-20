//
// Created by Gabriel on 4/16/2025.
//

#ifndef TURTLE_H
#define TURTLE_H
#include "Enemy.h"


class Turtle : public Enemy {
    //std::string MarioIDLE = "../Texture/all/Mario.png";
    static std::string TurtleRUN;
    static std::string FuriousRUN;
    // std::string MarioJUMP = "../Texture/all/MarioJumping.png";
    static int isd;
    int local_id = ++isd;

public:
    Turtle(float x, float y);

    void collision(Entity &other, int direction) override;

    static void collision();

    void update() override;

    void moveToTarget() override;

    [[nodiscard]] Turtle *clone() const override;

    Turtle &operator=(const Turtle &other);

    Turtle(const Turtle &other) = default;
};


#endif //TURTLE_H
