//
// Created by Gabriel on 5/14/2025.
//

#ifndef MOVEBLEENVIRONMENT_H
#define MOVEBLEENVIRONMENT_H

#include "Environment.h"

class MovebleEnvironment : public Environment {
    bool cont {true};
    public:
    MovebleEnvironment(float x, float y);
    void collision(Entity &other, int direction) override;
    void moveY();

    virtual void update();
    void moveToTarget();
};



#endif //MOVEBLEENVIRONMENT_H
