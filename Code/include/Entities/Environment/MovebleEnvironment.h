//
// Created by Gabriel on 5/14/2025.
//

#ifndef MOVEBLEENVIRONMENT_H
#define MOVEBLEENVIRONMENT_H

#include "Environment.h"
#include "../../Observer/ISubject.h"

// Movable environment entity that notifies observers on events
class MovebleEnvironment : public Environment, public ISubject,
                           public std::enable_shared_from_this<MovebleEnvironment> {
protected:
    bool cont{true};                    // Control flag for vertical movement phases
    std::vector<std::shared_ptr<IObserver>> observers; // List of subscribed observers

public:
    void attach(std::shared_ptr<IObserver> observer) override;   // Subscribe observer

    void detach(std::shared_ptr<IObserver> observer) override;   // Unsubscribe observer

    void notify(EventType event, std::shared_ptr<Entity> entity) override; // Notify all observers

    MovebleEnvironment(float x, float y);       // Constructor sets position and sound

    void collision(Entity &other, int direction) override; // Handle collisions

    void moveY();                 // Apply vertical movement logic (shake/fall)

    virtual void update();        // Update each frame (calls moveY)

    void moveToTarget();          // Commit movement to coords and reset state
};

#endif //MOVEBLEENVIRONMENT_H

