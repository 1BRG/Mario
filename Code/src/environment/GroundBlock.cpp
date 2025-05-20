//
// Created by Gabriel on 5/2/2025.
//

#include "../../include/entitati/environment/GroundBlock.h"

std::string GroundBlock::GroundBlockTexture = "../Texture/all/FloorTile.png";
GroundBlock *GroundBlock::clone() const {
        return new GroundBlock(*this);
}

GroundBlock::GroundBlock(const float dx, const float dy) : Environment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("GroundBlock");
    this->x = animations[IDLE]->width();
    this->y = animations[IDLE]->height();
    state = IDLE;

}

GroundBlock::~GroundBlock() {
    Environment::~Environment();
}
