//
// Created by Gabriel on 5/2/2025.
//

#ifndef BRICK_H
#define BRICK_H
#include "Environment.h"


class Brick: public Environment {
    static Animation* anim[3];
  public:
    static void InitStatics();

    Brick(const float dx, const float dy);
    Brick * clone() const override;
    Brick(const Brick& other) = default;
    ~Brick();
};



#endif //BRICK_H
