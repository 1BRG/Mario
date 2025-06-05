//
// Created by Gabriel on 5/2/2025.
//

#ifndef GroundBlock_H
#define GroundBlock_H
#include "Environment.h"

// Non-interactive ground tile that forms level floor
class GroundBlock : public Environment {
    static std::string GroundBlockTexture; // Path to ground tile texture

public:
    // No collision response needed for static floor
    void collision(Entity &other, int direction) override {
    }

    GroundBlock(float dx, float dy);          // Constructor sets position and sprite

    [[nodiscard]] GroundBlock *clone() const override; // Clone for map creation

    GroundBlock(const GroundBlock &other) = default;   // Default copy constructor

    ~GroundBlock() override;                 // Destructor cleanup
};

#endif //GroundBlock_H
