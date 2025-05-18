//
// Created by Gabriel on 4/1/2025.
//
#include <iostream>
#include "../include/entitati/Entity.h"

#include <string>

Entity::Entity(const float x, const float y, Animation *anim[4]) : coordX(x), coordY(y) {
    dt = 0;
    lastY = y;
    for (int i = 0; i < 4; ++i) {
        animations[i] = anim[i];
    }
    state = IDLE;
    this->x = animations[state]->width();
    this->y = animations[state]->height();
    targetX = coordX;
    targetY = coordY;
}

void Entity::print() const {
    std::cout << "Health: " << health << ";Danger: " << damage << std::endl;
}


[[nodiscard]] float Entity::coord_x() const {
    return coordX;
}

[[nodiscard]] float Entity::coord_y() const {
    return coordY;
}

[[nodiscard]] float Entity::width() const {
    return x;
}

[[nodiscard]] float Entity::height() const {
    return y;
}

[[nodiscard]] float Entity::target_x() const {
    return targetX;
}

[[nodiscard]] float Entity::target_y() const {
    return targetY;
}

float Entity::clamp(float val, float st, float dr) {
    if (val <= st)
        return st;
    if (val >= dr)
        return dr;
    return val;
}

void Entity::deltaTime(float deltatime) {
    dt = deltatime;
}

void Entity::draw(float cameraX) {
    animations[state]->Draw({coordX - cameraX, coordY}, WHITE, dt, false);
    // DrawTexture(texture, floor(coordX - cameraX), floor(coordY), WHITE);
    x = animations[state]->width();
    y = animations[state]->height();
}

bool Entity::isAlive() const {
    return health;
}

int Entity::danger() const {
    return damage;
};

//GPT
std::string Entity::detectCollisionSide(const std::shared_ptr<Entity> &env, int a, int b) const {

    Rectangle r1 = getRect(a, b);
    Rectangle r2 = env->getRect(0, 0);


    if (!CheckCollisionRecs(r1, r2)) return "NONE";


    float overlapX = std::min(r1.x + r1.width, r2.x + r2.width) - std::max(r1.x, r2.x);
    float overlapY = std::min(r1.y + r1.height, r2.y + r2.height) - std::max(r1.y, r2.y);

    if (overlapX < overlapY) {

        float centerX1 = r1.x + r1.width * 0.5f;
        float centerX2 = r2.x + r2.width * 0.5f;
        if (centerX1 < centerX2)
            return "RIGHT";
        else
            return "LEFT";
    } else {

        float centerY1 = r1.y + r1.height * 0.5f;
        float centerY2 = r2.y + r2.height * 0.5f;
        if (centerY1 < centerY2)
            return "BOTTOM";
        else
            return "TOP";
    }
}

//GPT
void Entity::decreaseX(float dec) {
    coordX -= dec;
    targetX = coordX;
}

Rectangle Entity::getRect(const int a, const int b) const {
    float dx = targetX + a, dy = targetY + b, width = this->width(), height = this->height();
    Rectangle rect = {dx, dy, width, height};
    return rect;
}

Entity::~Entity() {
    UnloadTexture(texture);
}


std::ostream &operator<<(std::ostream &os, const Entity &entity) {
    entity.print();
    return os;
}
