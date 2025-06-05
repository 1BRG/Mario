
//
// Created by Gabriel on 5/2/2025.
//

#include "../../include/Entities/Environment/GroundBlock.h"

std::string GroundBlock::GroundBlockTexture = "../Texture/all/FloorTile.png";

// Clone ground tile for prototype-based instantiation
GroundBlock *GroundBlock::clone() const {
    return new GroundBlock(*this);
}

// Initialize ground block sprite and dimensions
GroundBlock::GroundBlock(const float dx, const float dy) : Environment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("GroundBlock");
    this->x = animations[IDLE]->width();  // Set tile width
    this->y = animations[IDLE]->height(); // Set tile height
    state = IDLE;                         // Static idle state
}

// Destructor: rely on base class cleanup
GroundBlock::~GroundBlock() {
    Environment::~Environment();
}
