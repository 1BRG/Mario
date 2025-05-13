//
// Created by Gabriel on 5/2/2025.
//

#include "../include/entitati/Environment.h"

Environment::Environment(const float dx, const float dy, Animation *anim[3]) : Entity(dx, dy, anim) {
}

void Environment::collision(Entity &other, int direction) {
    bool ok = other.danger();
    if (direction == 0) {
        ok &= 1;
    }
}
