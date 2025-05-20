//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/entitati/environment/QuestionBlock.h"

std::string QuestionBlock::QuestionTexture = "../Texture/all/QuestionBlock.png";

std::string QuestionBlock::EmptyBlockTexture = "../Texture/all/EmptyBlock.png";

QuestionBlock::QuestionBlock(const float dx, const float dy) : MovebleEnvironment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("questionBlock");
    state = IDLE;
    health = 1e8;
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
}


void QuestionBlock::collision(Entity &other, int direction) {
    if (moving)
        MovebleEnvironment::collision(other, direction);
}

void QuestionBlock::update() {
    if (targetY != lastY && moving)
        animations[IDLE] = AnimationManager::animations.get("EmptyBlock");
    if (targetY != lastY)
        moving = false;
    MovebleEnvironment::update();
}

QuestionBlock *QuestionBlock::clone() const {
    return new QuestionBlock(*this);
}

QuestionBlock::~QuestionBlock() {
    MovebleEnvironment::~MovebleEnvironment();
}
