//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/entitati/environment/MovebleEnvironment.h"

MovebleEnvironment::MovebleEnvironment(const float dx, const float dy) : Environment(dx, dy) {
}


void MovebleEnvironment::collision(Entity &other, int direction) {
    if (direction == 1 && moving) {
        targetY -= 1;
        if (other.danger() > health)
        health = 0;
    }
}

void MovebleEnvironment::moveY() {
        if (targetY != lastY && cont == false)
             targetY = std::min(targetY+ Jump * dt * 0.5, double(lastY)), updateBottom = true;
        else if (targetY != lastY && cont == true) {
            if (targetY > lastY - 8 && lastY != screenHeight)
                 targetY -= Jump * dt * 0.5, updateTop = true;
            else cont = false;
        }
}
void MovebleEnvironment::update() {
    moveY();
}

void MovebleEnvironment::moveToTarget() {
    coordY = targetY;
    if (coordY == lastY)
        cont = true, state = IDLE;
}

