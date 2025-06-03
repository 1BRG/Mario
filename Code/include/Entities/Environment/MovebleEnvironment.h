//
// Created by Gabriel on 5/14/2025.
//

#ifndef MOVEBLEENVIRONMENT_H
#define MOVEBLEENVIRONMENT_H

#include "Environment.h"
#include "../../Observer/ISubject.h"

class MovebleEnvironment : public Environment, public ISubject,
                           public std::enable_shared_from_this<MovebleEnvironment> {
protected:
    bool cont{true};
    std::vector<std::shared_ptr<IObserver> > observers;

public:
    void attach(std::shared_ptr<IObserver> observer) override;

    void detach(std::shared_ptr<IObserver> observer) override;

    void notify(EventType event, std::shared_ptr<Entity> entity) override;

    MovebleEnvironment(float x, float y);

    void collision(Entity &other, int direction) override;

    void moveY();

    virtual void update();

    void moveToTarget();
};


#endif //MOVEBLEENVIRONMENT_H
