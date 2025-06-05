//
// Created by Gabriel on 5/19/2025.
//

#ifndef RESOURCEANIMATION_H
#define RESOURCEANIMATION_H

#include "ResourceManager.h"
#include "../Entities/Animation.h"

// Global access point for Animation resources
struct AnimationManager {
    inline static ResourceManager<Animation> animations; // Manager for Animation objects
};

#endif //RESOURCEANIMATION_H
