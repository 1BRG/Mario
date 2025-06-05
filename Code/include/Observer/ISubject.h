
//
// Created by Gabriel on 6/2/2025.
//

#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>
#include "IObserver.h"

// Subject interface: manages observers and notifies them of events
class ISubject {
public:
    virtual ~ISubject() = default;

    // Subscribe an observer to receive events
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;

    // Unsubscribe an observer
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;

    // Notify all observers of an event
    virtual void notify(EventType event, std::shared_ptr<Entity> entity) = 0;
};

#endif //ISUBJECT_H
