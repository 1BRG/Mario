//
// Created by Gabriel on 5/2/2025.
//

#include "../include/entitati/Brick.h"

 Animation* Brick:: anim[3] = {
nullptr, nullptr, nullptr};
void Brick::InitStatics() {
    if (anim[0] == nullptr) {
        anim[0] = new Animation("../Texture/all/BrickBlockBrown.png", 1, 6);
        anim[1] = new Animation("../Texture/all/BrickBlockBrown.png", 1,12);
        anim[2] = new Animation("../Texture/all/BrickBlockBrown.png", 1, 4);
    }
}


Brick:: Brick(const float dx, const float dy) : Environment(dx, dy, anim) {
    if (anim[0] == nullptr) {
        anim[0] = new Animation(BrickTexture, 1, 6);
        anim[1] = new Animation(BrickTexture, 1, 12);
        anim[2] = new Animation(BrickTexture, 1, 4);
    }
    state = IDLE;
}
Brick * Brick::clone() const {
    {
        return new Brick(*this);
    }
}

Brick::~Brick() {
    Environment::~Environment();
    for (int i = 0; i < 3; ++i) {
        delete anim[i];
        anim[i] = nullptr;
    }
}
