//
// Created by Gabriel on 5/14/2025.
//

#ifndef BRICKBLOCK_H
#define BRICKBLOCK_H

#include "MovebleEnvironment.h"

// Breakable brick block that notifies observers on destruction
class BrickBlock : public MovebleEnvironment {
    static std::string BrickTexture;     // Path to brick block texture
    bool broken{false};                  // Flag if the block has been broken

public:
    BrickBlock(float dx, float dy);     // Constructor sets position and initial state

    BrickBlock(const BrickBlock &other) = default; // Default copy constructor

    void collision(Entity &other, int direction) override; // Handle hit from below

    void update() override;             // Update movement if any

    [[nodiscard]] BrickBlock *clone() const override; // Clone for level population

    ~BrickBlock() override;             // Destructor cleanup
};

#endif //BRICKBLOCK_H