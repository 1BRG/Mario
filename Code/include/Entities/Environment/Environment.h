//
// Created by Gabriel on 5/2/2025.
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "../Entity.h"

// Static environment entity: non-interactive world elements
class Environment : public Entity {
public:
    Environment(float x, float y);  // Constructor sets position

    Environment() = default;         // Default constructor
};

#endif //ENVIRONMENT_H
