//
// Created by Gabriel on 4/1/2025.
//

#ifndef ENTITATI_H
#define ENTITATI_H

#include <cmath>
#include <memory>
#include <raylib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "../defineuri.h"
#include "../Exception/Exception.h"
#include "Animation.h"
#include "../Template/templateFunction.h"
#include "../Template/ResourceAnimation.h"
#include "../Template/ResourceAudio.h"

// Base class for all game entities (player, enemies, items)
class Entity {
    // Internal struct for detailed collision data
    struct CollisionInfo {
        float time; // Time of collision within frame
        Vector2 normal; // Collision surface normal
        bool collided; // Flag if collision occurred
    };

protected:
    Vector2 velocity{0, 0}; // Current movement velocity

    // Possible animation states
    enum State { IDLE, RUN, JUMP, SKIDDING };

    std::unordered_map<State, std::shared_ptr<Animation> > animations; // Animations per state

    // Sound effects for entity actions
    enum Sound { DIE, JUMPPING, COIN };

    std::unordered_map<Sound, std::shared_ptr<Audio> > sounds; // Loaded audio resources

    Vector2 position{}; // Current world position
    State state; // Current state for animation logic
    float dt; // Delta time accumulator
    std::string texturePath; // Path to texture resource
    float coordX{0}, coordY{0}; // Actual drawing coordinates
    float x{0}, y{0}; // Dimensions of current frame
    float targetX{0}, targetY{0}; // Next target position after movement
    int health{1}; // Remaining health points
    bool moving{true}; // Movement enabled flag
    int damage{0}; // Damage inflicted on collision
    // Flags to enable per-side collision updates
    bool updateLeft{true}, updateRight{true}, updateTop{true}, updateBottom{true};
    Texture2D texture{}; // Loaded texture for drawing
    float lastY{screenHeight}; // Previous frame Y-coordinate for fall detection

public:
    // Check if entity moved upward in last update
    bool lasty() { return targetY < lastY; }

    static void INIT(); // Initialize static resources

    virtual void incomingDamage() {
    } // Handle logic when taking damage
    virtual void collision(Entity &other, int direction) = 0; // Collision response interface

    [[nodiscard]] std::string detectCollisionSide(const std::shared_ptr<Entity> &env, int a, int b) const;

    // Determine collision side

    // Constructor setting initial position
    Entity(float x, float y);

    virtual void print() const; // Debug print entity status
    friend std::ostream &operator<<(std::ostream &os, const Entity &entity);

    Entity() = default; // Default constructor

    // Accessors for position and size
    [[nodiscard]] float coord_x() const;

    [[nodiscard]] float coord_y() const;

    [[nodiscard]] float height() const;

    [[nodiscard]] float width() const;

    [[nodiscard]] float target_x() const;

    [[nodiscard]] float target_y() const;

    [[nodiscard]] int danger() const; // Damage value
    [[nodiscard]] bool isAlive() const; // Check if health > 0

    virtual void draw(float cameraX); // Render entity using current animation
    void deltaTime(float deltatime); // Set delta time for animations
    [[nodiscard]] virtual Entity *clone() const = 0; // Create a copy of this entity
    void decreaseX(float dec); // Move entity left by dec units
    [[nodiscard]] Rectangle getRect(int a, int b) const; // Get bounding rectangle at offset
    virtual ~Entity(); // Cleanup resources
};

#endif // ENTITATI_H
