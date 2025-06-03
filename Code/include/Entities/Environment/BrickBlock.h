//
// Created by Gabriel on 5/14/2025.
//

#ifndef BRICKBLOCK_H
#define BRICKBLOCK_H

#include "MovebleEnvironment.h"

class BrickBlock : public MovebleEnvironment {
    static std::string BrickTexture;
    bool broken{false};

public:
    BrickBlock(float dx, float dy);

    BrickBlock(const BrickBlock &other) = default;

    void collision(Entity &other, int direction) override;

    void update() override;

    [[nodiscard]] BrickBlock *clone() const override;

    ~BrickBlock() override;
};


#endif //BRICKBLOCK_H
