//
// Created by Gabriel on 5/2/2025.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Entity.h"


//class Enemy : public
class Environment : public Entity
{
public:
    Environment(float x, float y, Animation* anim[3]);
    Environment() = default;
    void collision(Entity &other, int direction) override;
};



#endif //ENVIRONMENT_H
