
//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/Entities/Environment/BrickBlock.h"

std::string BrickBlock::BrickTexture = "../Texture/all/BrickBlockBrown.png";

// Initialize brick block with sprite and one-hit breakable health
BrickBlock::BrickBlock(const float dx, const float dy) : MovebleEnvironment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("BrickBlock");
    state = IDLE;                          // Start idle
    health = 1;                            // Breakable with one hit
    this->x = animations[IDLE]->width();  // Set dimensions
    this->y = animations[IDLE]->height();
}

// On downward hit: break if damage exceeds health, notify observers
void BrickBlock::collision(Entity &other, int direction) {
    if (!broken && direction == 1) {
        MovebleEnvironment::collision(other, direction); // Small bounce
        if (other.danger() > health) {
            health = 0;
            sounds[DIE]->play();            // Play break sound

            std::shared_ptr<MovebleEnvironment> This = shared_from_this();
            notify(Brick_break, This);      // Notify observers of break event
            broken = true;                   // Mark as broken
        }
    }
}

// No extra behavior, just call base update
void BrickBlock::update() {
    MovebleEnvironment::update();
}

// Clone for prototype instantiation
BrickBlock *BrickBlock::clone() const {
    return new BrickBlock(*this);
}

// Destructor: rely on base class cleanup
BrickBlock::~BrickBlock() {
    MovebleEnvironment::~MovebleEnvironment();
}
