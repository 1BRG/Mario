//
// Created by Gabriel on 4/1/2025.
//
#include <iostream>
#include "../include/entitati/Entity.h"


Entity::Entity(const double x, const double y, const Texture2D &Texture) : coordX(x), coordY(y), texture(Texture) {
    this->x =  Texture.width;
    this->y =  Texture.height;
    targetX = coordX;
    targetY = coordY;
}

Entity::Entity(const Texture2D &Texture) : texture(Texture) {
    this->x =  Texture.width;
    this->y =  Texture.height;
};

[[nodiscard]] double Entity::coord_x() const {
    return coordX;
}

[[nodiscard]] double Entity::coord_y() const {
    return coordY;
}

[[nodiscard]] double Entity::width() const {
    return x;
}

[[nodiscard]] double Entity::height() const {
    return y;
}

[[nodiscard]] double Entity::target_x() const {
    return targetX;
}

[[nodiscard]] double Entity::target_y() const {
    return targetY;
}
double Entity::clamp(double x, double st, double dr) {
    if (x <= st)
        return st;
    if (x >= dr)
        return dr;
    return x;
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



Enviroment::Enviroment(const double x, const double y) : Entity(x, y, BrickTexture) {
}

Enviroment::Enviroment() {
    texture = BrickTexture;
}




