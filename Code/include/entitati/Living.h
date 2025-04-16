//
// Created by Gabriel on 4/16/2025.
//

#ifndef LIVING_H
#define LIVING_H
#include "Entity.h"


class Living : public Entity {
protected:
    double speed = 0;
    double lastY = screenHeight;
    bool canJump = true, cont = true, isJumping = false;
    bool tookDamage = false;
    void moveX();
    void moveY();
public:
    Living(double x, double y, const Texture2D &Texture);
    explicit Living(const Texture2D &texture);
    Living() = default;
    [[nodiscard]] bool isAlive() const;
    virtual void moveToTarget(){}
    virtual void setLastY();
    virtual void collision(Entity &other, int directie);
};



#endif //LIVING_H
