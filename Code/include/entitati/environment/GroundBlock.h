//
// Created by Gabriel on 5/2/2025.
//

#ifndef GroundBlock_H
#define GroundBlock_H
#include "Environment.h"


class GroundBlock : public Environment {
static std::string GroundBlockTexture;
public:
    void collision(Entity &other, int direction) override {}

    GroundBlock( float dx,  float dy);

     [[nodiscard]] GroundBlock *clone() const override;

    GroundBlock(const GroundBlock &other) = default;

    ~GroundBlock() override;
};


#endif //GroundBlock_H
