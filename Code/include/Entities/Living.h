//
// Created by Gabriel on 4/16/2025.
//

#ifndef LIVING_H
#define LIVING_H
#include "Entity.h"


class Living : public Entity {
protected:
    float speed{0};
    bool canJump{true}, cont{true}, isJumping{false};
    bool tookDamage{false};

    void moveX();

    void moveY();

public:
    Living(float x, float y);

    Living() = default;

    void draw(float cameraX) override;

    virtual void moveToTarget() = 0;

    virtual void setLastY();

    void collision(Entity &other, int directie) override;

    void print() const override;

    [[nodiscard]] bool inCollision(const std::shared_ptr<Entity> &env, int a, int b) const;

    virtual void update() = 0;

    friend std::ostream &operator<<(std::ostream &os, const Living &living);

    bool bottomCollision(const std::shared_ptr<Entity> &env) const;

    bool topCollision(const std::shared_ptr<Entity> &env) const;

    bool leftCollision(const std::shared_ptr<Entity> &env) const;

    bool rightCollision(const std::shared_ptr<Entity> &env) const;
};


#endif //LIVING_H
