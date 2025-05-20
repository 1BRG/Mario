//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/entitati/environment/BrickBlock.h"

std::string BrickBlock::BrickTexture = "../Texture/all/BrickBlockBrown.png";


BrickBlock::BrickBlock(const float dx, const float dy) : MovebleEnvironment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("BrickBlock");
    state = IDLE;
    health = 1;
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
}


void BrickBlock::collision(Entity &other, int direction) {
    if (moving)
        MovebleEnvironment::collision(other, direction);
}

void BrickBlock::update() {
    MovebleEnvironment::update();
}

BrickBlock *BrickBlock::clone() const {
    return new BrickBlock(*this);
}

BrickBlock::~BrickBlock() {
    MovebleEnvironment::~MovebleEnvironment();
}
