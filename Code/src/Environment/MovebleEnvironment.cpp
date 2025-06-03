//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/Entities/Environment/MovebleEnvironment.h"

void MovebleEnvironment::attach(std::shared_ptr<IObserver> observer) {
    observers.push_back(observer);
}

void MovebleEnvironment::detach(std::shared_ptr<IObserver> observer) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers.at(i) == observer) {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

void MovebleEnvironment::notify(EventType event, std::shared_ptr<Entity> entity) {
    for (const auto &observer: observers) {
        observer->onNotify(event, entity);
    }
}

MovebleEnvironment::MovebleEnvironment(const float dx, const float dy) : Environment(dx, dy) {
    sounds[DIE] = ResourceAudio::audio.get("brickDestroy");
}


void MovebleEnvironment::collision(Entity &other, int direction) {
    if (direction == 1 && moving) {
        targetY -= 1;
    }
}

void MovebleEnvironment::moveY() {
    if (targetY != lastY && cont == false)
        targetY = std::min(targetY + Jump * dt * 0.5, double(lastY)), updateBottom = true;
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
