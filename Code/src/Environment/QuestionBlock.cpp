
//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/Entities/Environment/QuestionBlock.h"

std::string QuestionBlock::QuestionTexture = "../Texture/all/QuestionBlock.png";
std::string QuestionBlock::EmptyBlockTexture = "../Texture/all/EmptyBlock.png";

// Initialize question block with sprite and high health to prevent destruction
QuestionBlock::QuestionBlock(const float dx, const float dy) : MovebleEnvironment(dx, dy) {
    animations[IDLE] = AnimationManager::animations.get("questionBlock");
    state = IDLE;                          // Start in idle state
    health = 1e8;                          // Effectively indestructible
    this->x = animations[IDLE]->width();  // Set dimensions
    this->y = animations[IDLE]->height();
}

// Link block to the game world for spawning
void QuestionBlock::setWorld(game *g) {
    world = g;
}

// On downward hit when active, spawn coin, change texture, notify observers
void QuestionBlock::collision(Entity &other, int direction) {
    if (active && direction == 1) {
        MovebleEnvironment::collision(other, direction); // Small bounce
        animations[IDLE] = AnimationManager::animations.get("EmptyBlock");
        active = false;                      // Mark as used
        world->insertEntity(std::make_shared<Coin>(coordX + x / 4, coordY - y)); // Spawn coin

        std::shared_ptr<MovebleEnvironment> This = shared_from_this();
        notify(Question_hit, This);         // Notify observers of hit event
    }
}

// Update block animation: remain empty when moving, then settle
void QuestionBlock::update() {
    if (targetY != lastY && moving)
        animations[IDLE] = AnimationManager::animations.get("EmptyBlock");

    if (targetY != lastY)
        moving = false;                      // Stop movement after initial bounce
    MovebleEnvironment::update();            // Continue vertical motion
}

// Clone for prototype-based spawning
QuestionBlock *QuestionBlock::clone() const {
    return new QuestionBlock(*this);
}

// Destructor: rely on base class cleanup
QuestionBlock::~QuestionBlock() {
    MovebleEnvironment::~MovebleEnvironment();
}
