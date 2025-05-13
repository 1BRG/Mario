//
// Created by Gabriel on 5/2/2025.
//

#ifndef BRICK_H
#define BRICK_H
#include "Environment.h"


class Brick : public Environment {
    static Animation *anim[3];

public:
    static void InitStatics();

    Brick( float dx,  float dy);

    [[nodiscard]] Brick *clone() const override;

    Brick(const Brick &other) = default;

    ~Brick() override;
};


#endif //BRICK_H
