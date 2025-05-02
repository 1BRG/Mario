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

void Entity::draw(int cameraX) {

    DrawTexture(texture, floor(coordX - cameraX), floor(coordY), WHITE);
}

void Entity::update() {
}

int Entity::danger() const {
    return damage;
};

void Entity::collision(Entity &other, int direction) {
    //bs
    bool ok = other.danger();
    if (direction == 1) {
        ok &= 1;
    }
}
//GPT
std::string Entity::detectCollisionSide(const std::shared_ptr<Entity>& env, int a, int b) const {
    // 1) Construim cele două Rectangle fără offset-uri „magice”
    Rectangle r1 = getRect(a, b);             // dreptunghiul nostru la poziția targetX/Y
    Rectangle r2 = env->getRect(0, 0);        // dreptunghiul entității cu care testăm

    // 2) Dacă nu se intersectează, nu avem coliziune
    if (!CheckCollisionRecs(r1, r2)) return "NONE";

    // 3) Calculăm overlapii pe fiecare axă
    float overlapX = std::min(r1.x + r1.width,  r2.x + r2.width)  - std::max(r1.x, r2.x);
    float overlapY = std::min(r1.y + r1.height, r2.y + r2.height) - std::max(r1.y, r2.y);

    // 4) Pe axa cu suprapunere mai mică e coliziunea „principală”
    if (overlapX < overlapY) {
        // stânga/dreapta
        float centerX1 = r1.x + r1.width * 0.5f;
        float centerX2 = r2.x + r2.width * 0.5f;
        if (centerX1 < centerX2)
            return "RIGHT";  // lovim partea stângă a lui env
        else
            return "LEFT";   // lovim partea dreaptă a lui env
    } else {
        // sus/jos
        float centerY1 = r1.y + r1.height * 0.5f;
        float centerY2 = r2.y + r2.height * 0.5f;
        if (centerY1 < centerY2)
            return "BOTTOM"; // lovim partea de sus a lui env
        else
            return "TOP";    // lovim partea de jos a lui env
    }
}
//GPT
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




