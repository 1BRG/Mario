//
// Created by Gabriel on 4/16/2025.
//

#ifndef LIVING_H
#define LIVING_H
#include "Entity.h"



class Living : public Entity {
protected:
    float speed = 0;
    float lastY = screenHeight;
    bool canJump = true, cont = true, isJumping = false;
    bool tookDamage = false;
    void moveX();
    void moveY();
public:
    Living(float x, float y, std::string &texturePath);
    explicit Living(std::string &texturePath);
    Living() = default;
    [[nodiscard]] bool isAlive() const;
    virtual void moveToTarget(){}
    virtual void setLastY();
    virtual void collision(Entity &other, int directie);
    bool inCollision(const std::shared_ptr<Entity> &env, int a, int b) const;
    virtual void update() = 0;
    bool bottomCollision(const std::shared_ptr<Entity> & env);

    bool topCollision(const std::shared_ptr<Entity> & env);

    bool leftCollision(const std::shared_ptr<Entity> & env);

    bool rightCollision(const std::shared_ptr<Entity> & env);
};



#endif //LIVING_H
