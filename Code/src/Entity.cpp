
//
// Created by Gabriel on 4/1/2025.
//
#include <iostream>
#include "../include/Entities/Entity.h"
#include <string>

// Initialize entity at given coordinates
Entity::Entity(const float x, const float y) : coordX(x), coordY(y) {
    dt = 0;
    lastY = y;
    state = IDLE;
    targetX = coordX;
    targetY = coordY;
}

// Output health and damage for debugging
void Entity::print() const {
    std::cout << "Health: " << health << ";Danger: " << damage << std::endl;
}

// Position getters
[[nodiscard]] float Entity::coord_x() const {
    return coordX;
}

[[nodiscard]] float Entity::coord_y() const {
    return coordY;
}

// Dimension getters
[[nodiscard]] float Entity::width() const {
    return x;
}

[[nodiscard]] float Entity::height() const {
    return y;
}

// Target position getters
[[nodiscard]] float Entity::target_x() const {
    return targetX;
}

[[nodiscard]] float Entity::target_y() const {
    return targetY;
}

// Store delta time for frame updates
void Entity::deltaTime(float deltatime) {
    dt = deltatime;
}

// Draw current animation frame at world position adjusted by camera
void Entity::draw(float cameraX) {
    animations[state]->Draw({coordX - cameraX, coordY}, WHITE, dt, false);
    // Update width/height based on current animation frame
    x = animations[state]->width();
    y = animations[state]->height();
}

// Check if entity still has health
bool Entity::isAlive() const {
    return health;
}

// Retrieve damage value
int Entity::danger() const {
    return damage;
}

// Determine which side collided with another entity
std::string Entity::detectCollisionSide(const std::shared_ptr<Entity> &env, int a, int b) const {
    Rectangle r1 = getRect(a, b);
    Rectangle r2 = env->getRect(0, 0);
    if (!CheckCollisionRecs(r1, r2)) return "NONE";

    float overlapX = std::min(r1.x + r1.width, r2.x + r2.width) - std::max(r1.x, r2.x);
    float overlapY = std::min(r1.y + r1.height, r2.y + r2.height) - std::max(r1.y, r2.y);

    // Decide collision axis by smaller overlap
    if (overlapX < overlapY) {
        float centerX1 = r1.x + r1.width * 0.5f;
        float centerX2 = r2.x + r2.width * 0.5f;
        return (centerX1 < centerX2) ? "RIGHT" : "LEFT";
    } else {
        float centerY1 = r1.y + r1.height * 0.5f;
        float centerY2 = r2.y + r2.height * 0.5f;
        return (centerY1 < centerY2) ? "BOTTOM" : "TOP";
    }
}

// Move left and sync target position
void Entity::decreaseX(float dec) {
    coordX -= dec;
    targetX = coordX;
}

// Construct bounding rectangle at offset (a,b)
Rectangle Entity::getRect(const int a, const int b) const {
    float dx = targetX + a;
    float dy = targetY + b;
    Rectangle rect = {dx, dy, width(), height()};
    return rect;
}

// Unload texture resource on destruction
Entity::~Entity() {
    UnloadTexture(texture);
}

// Stream insertion uses print()
std::ostream &operator<<(std::ostream &os, const Entity &entity) {
    entity.print();
    return os;
}
