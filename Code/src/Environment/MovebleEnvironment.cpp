
//
// Created by Gabriel on 5/14/2025.
//

#include "../../include/Entities/Environment/MovebleEnvironment.h"

// Add an observer to the list
void MovebleEnvironment::attach(std::shared_ptr<IObserver> observer) {
    observers.push_back(observer);
}

// Remove an observer from the list
void MovebleEnvironment::detach(std::shared_ptr<IObserver> observer) {
    for (int i = 0; i < observers.size(); i++) {
        if (observers.at(i) == observer) {
            observers.erase(observers.begin() + i);
            break;
        }
    }
}

// Notify all subscribed observers of an event
void MovebleEnvironment::notify(EventType event, std::shared_ptr<Entity> entity) {
    for (const auto &observer: observers) {
        observer->onNotify(event, entity);
    }
}

// Initialize movable environment and load destruction sound
MovebleEnvironment::MovebleEnvironment(const float dx, const float dy) : Environment(dx, dy) {
    sounds[DIE] = ResourceAudio::audio.get("brickDestroy");
}

// On top-side collision, trigger a small downward movement
void MovebleEnvironment::collision(Entity &other, int direction) {
    if (direction == 1 && moving) {
        targetY -= 1;
    }
}

// Vertical movement logic: shake up then down back to lastY
void MovebleEnvironment::moveY() {
    if (targetY != lastY && cont == false)
        targetY = std::min(targetY + Jump * dt * 0.5, double(lastY)), updateBottom = true;
    else if (targetY != lastY && cont == true) {
        if (targetY > lastY - 8 && lastY != screenHeight)
            targetY -= Jump * dt * 0.5, updateTop = true;
        else cont = false;
    }
}

// Update frame logic
void MovebleEnvironment::update() {
    moveY();
}

// Apply target Y and reset control flag when at rest
void MovebleEnvironment::moveToTarget() {
    coordY = targetY;
    if (coordY == lastY)
        cont = true, state = IDLE;
}
