//
// Created by Gabriel on 4/16/2025.
//

#ifndef LIVING_H
#define LIVING_H
#include "Entity.h"

// Class for entities with movement and jumping capabilities
class Living : public Entity {
protected:
    float speed{0}; // Current horizontal speed
    bool canJump{true}, // Flag if entity can initiate jump
            cont{true}, // Control flag for jump continuation
            isJumping{false}; // Flag if currently jumping
    bool tookDamage{false}; // Flag if damage was taken this frame

    void moveX(); // Handle horizontal movement

    void moveY(); // Handle vertical movement (gravity/jump)

public:
    Living(float x, float y); // Constructor with initial position

    Living() = default;

    void draw(float cameraX) override; // Override draw to include flip based on speed

    virtual void moveToTarget() = 0; // Move logic towards a target position

    virtual void setLastY(); // Update lastY when landing reset

    void collision(Entity &other, int directie) override; // Handle collision with other entities

    void print() const override; // Print debug info including speed

    [[nodiscard]] bool inCollision(const std::shared_ptr<Entity> &env, int a, int b) const; // AABB check

    virtual void update() = 0; // Update logic each frame

    friend std::ostream &operator<<(std::ostream &os, const Living &living); // Stream output

    // Check collision on specific sides
    bool bottomCollision(const std::shared_ptr<Entity> &env) const;

    bool topCollision(const std::shared_ptr<Entity> &env) const;

    bool leftCollision(const std::shared_ptr<Entity> &env) const;

    bool rightCollision(const std::shared_ptr<Entity> &env) const;
};

#endif //LIVING_H
