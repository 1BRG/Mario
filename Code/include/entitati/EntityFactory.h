//
// Created by Gabriel on 5/21/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include "includeAll.h"


class EntityFactory {

public:
    enum Type {brickBlock, groundBlock, questionBlock, player, turtle};
    EntityFactory() = default;
    template<typename... Args>
    static std::shared_ptr<Entity> createEntity(Type type, Args&&... args) {
        if (type == brickBlock)
            return std::make_shared<BrickBlock>(args...);
        if (type == groundBlock)
            return std::make_shared<GroundBlock>(args...);
        if (type == questionBlock)
            return std::make_shared<QuestionBlock>(args...);
        if (type == player)
            return std::make_shared<Player>(args...);
        if (type == turtle)
            return std::make_shared<Turtle>(args...);
        throw std::invalid_argument("Invalid type");
    }
};



#endif //ENTITYFACTORY_H
