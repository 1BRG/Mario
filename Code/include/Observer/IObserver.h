//
// Created by Gabriel on 6/2/2025.
//

#ifndef IOBSERVER_H
#define IOBSERVER_H
#include <memory>
#include "../Entities/Entity.h"

// Types of events that observers can react to
enum EventType {
    Brick_break,       // A brick block was broken
    Question_hit,      // A question block was hit
    Coin_spawn,        // A coin was spawned (notifies on world event)
    Coin_collected,    // A coin was collected
    PowerUp_spawn,     // A power-up was spawned
    PowerUp_collected, // A power-up was collected
};

// Observer interface for receiving event notifications
class IObserver {
public:
    virtual ~IObserver() = default;

    // Called by subject when an event occurs, passing event type and entity involved
    virtual void onNotify(EventType event, std::shared_ptr<Entity> entity) = 0;
};

#endif //IOBSERVER_H