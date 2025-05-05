//
// Created by Gabriel on 5/2/2025.
//

#ifndef BRICK_H
#define BRICK_H
#include "Environment.h"


class Brick: public Environment {

  public:
    Brick(const float dx, const float dy);
    Brick * clone() const override;
};



#endif //BRICK_H
