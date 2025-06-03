//
// Created by Gabriel on 6/2/2025.
//

#ifndef COIN_H
#define COIN_H

#include "Entity.h"

#include "../../include/Template/ResourceAnimation.h"
#include "../../include/Template/ResourceAudio.h"
#include "../Entities/Player.h"

#include <iostream>
#include "../observer/ISubject.h"

class Coin : public Entity {
    bool collected{false};

public:
    Coin(float x, float y);

    ~Coin() override = default;

    bool isCollected() const;

    void collect();

    void collision(Entity &other, int direction) override;

    [[nodiscard]] Coin *clone() const override;
};


#endif //COIN_H
