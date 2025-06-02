//
// Created by Gabriel on 4/16/2025.
//

#include "../include/entitati/Turtle.h"

#include <iostream>
#include "../include/entitati/Coin.h"
int Turtle::isd = 0;

std::string Turtle::TurtleRUN = "../Texture/all/TurtleRun.png";
std::string Turtle::FuriousRUN = "../Texture/all/FuriousRunFixed.png";

Turtle::Turtle(const float x, const float y) : Enemy(x, y) {
    animations[IDLE] = AnimationManager::animations.get("turtle_idle");
    animations[JUMP] = AnimationManager::animations.get("turtle_jump");
    animations[RUN] = AnimationManager::animations.get("turtle_run");
    sounds[DIE] = ResourceAudio::audio.get("kickKill");
    health = 2;
    damage = 1;
    state = RUN;
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
    speed = DefaultSpeed;
}

Turtle *Turtle::clone() const {
    return new Turtle(*this);
}

Turtle &Turtle::operator=(const Turtle &other) {
    if (this == &other)
        return *this;
    UnloadTexture(texture);
    Enemy::operator=(other);
    damage = other.damage;
    speed = other.speed;
    health = other.health;

    texture = LoadTexture(other.texturePath.c_str());
    if (texture.id == 0)
        throw TextureException(texturePath);
    x = texture.width;
    y = texture.height;
    return *this;
}

void Turtle::update() {
    moveX();
    moveY();
}

void Turtle::collision(Entity &other, int direction) {
    if (auto coin = dynamic_cast<Coin*>(&other); coin != nullptr) {
        return;
    }
    if (direction == 1) {
        //  updateBottom = false;
        if (other.lasty()) {
            bool ok;
            ok = true;
        }
        targetY = std::min(targetY, other.coord_y() - y);
        lastY = targetY;
    } else if (direction == -1) {
        cont = false;
        //    updateTop = false;
        cont = false;
        canJump = false;
    } else if (direction == 2) {
        targetX = std::min(targetX, other.coord_x() - x), change = true;
    } else if (direction == -2) {
        targetX = std::max(targetX, other.coord_x() + other.width()), change = true;
    }
    if (other.danger() > 1)
        tookDamage = true;
}


void Turtle::moveToTarget() {
    if (change) speed *= -1;
    else coordX = targetX, coordY = targetY;
    change = false;
    if (tookDamage) {
        health--;
        health = clamp(health, 0, 1000000);
        try {
            auto furiousAnim = AnimationManager::animations.get("furiousRun");
            animations[RUN]  = furiousAnim;
            animations[JUMP] = animations[IDLE] =  furiousAnim;
        }
        catch (TextureException ex) {
            std::cout << ex.what() << std::endl;
            exit(0);
        }
        sounds[DIE]->play();
        damage = 2;


     //   animations[IDLE] = animations[RUN];
        speed *= 3;
        tookDamage = false;
    } else {
        tookDamage = false;
        targetY = coordY;
        targetX = coordX;
    }
}
