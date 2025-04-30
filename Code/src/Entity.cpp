//
// Created by Gabriel on 4/1/2025.
//
#include <iostream>
#include "../include/entitati/Entity.h"


Entity::Entity(const float x, const float y, const Texture2D &Texture) : coordX(x), coordY(y), texture(Texture) {
    this->x =  Texture.width;
    this->y =  Texture.height;
    targetX = coordX;
    targetY = coordY;
}

Entity::Entity(const Texture2D &Texture) : texture(Texture) {
    this->x =  Texture.width;
    this->y =  Texture.height;
};

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
float Entity::clamp(float x, float st, float dr) {
    if (x <= st)
        return st;
    if (x >= dr)
        return dr;
    return x;
}
void Entity::deltaTime(float dt) {
    this->dt = dt;
}

void Entity::draw() {
    DrawTexture(texture, floor(coordX), floor(coordY), WHITE);
}

void Entity::update() {
}

int Entity::danger() const {
    return damage;
};
void Entity::collision(Entity &other, int direction) {
}
void Entity::decreaseX(int dec) {
    coordX -= dec;
    targetX = coordX;
}

Rectangle Entity::getRect(const int a, const int b) const {
    float x = targetX + a, y = targetY + b, width = this->width(), height = this->height();
    Rectangle rect = {x, y, width, height};
    return rect;
}


Enviroment::Enviroment(const float x, const float y) : Entity(x, y, BrickTexture) {
}

Enviroment::Enviroment() {
    texture = BrickTexture;
}




