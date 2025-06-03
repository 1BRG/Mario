//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/Entities/Environment/BrickBlock.h"

std::string BrickBlock::BrickTexture = "../Texture/all/BrickBlockBrown.png";


BrickBlock::BrickBlock(const float dx, const float dy) : MovebleEnvironment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("BrickBlock");
    state = IDLE;
    health = 1;
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
}


void BrickBlock::collision(Entity &other, int direction) {
    if (broken == false && direction == 1) {
        MovebleEnvironment::collision(other, direction);
        if (other.danger() > health) {
            health = 0, sounds[DIE]->play();

            std::shared_ptr<MovebleEnvironment> This = shared_from_this();
            notify(Brick_break, This);
        }
    }
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
