//
// Created by Gabriel on 6/2/2025.
//

#ifndef ISUBJECT_H
#define ISUBJECT_H


#include <memory>

#include "IObserver.h"
#include "IObserver.h"
class ISubject {

  public:
    virtual ~ISubject() = default;
    virtual void attach(std::shared_ptr<IObserver> observer) = 0;
    virtual void detach(std::shared_ptr<IObserver> observer) = 0;
    virtual void notify(EventType event, std::shared_ptr<Entity> entity) = 0;
};



#endif //ISUBJECT_H
