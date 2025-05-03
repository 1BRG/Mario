//
// Created by Gabriel on 5/2/2025.
//

#include "../include/entitati/Environment.h"

Environment::Environment(const float dx, const float dy, std::string &texturePath) : Entity(dx, dy, texturePath) {
}

void Environment::collision(Entity &other, int direction) {
    bool ok = other.danger();
    if (direction == 0) {
        ok &= 1;
    }
}
