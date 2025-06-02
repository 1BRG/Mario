//
// Created by Gabriel on 6/2/2025.
//

#ifndef IOBSERVER_H
#define IOBSERVER_H
#include "../entitati/Entity.h"

enum EventType {
    Brick_break,
    Question_hit,
    Coin_spawn,
    Coin_collected,
    PowerUp_spawn,
    PowerUp_collected,
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onNotify(EventType event, std::shared_ptr<Entity> entity) = 0;
};



#endif //IOBSERVER_H
