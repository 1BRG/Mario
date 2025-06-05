//
// Created by Gabriel on 5/21/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H
#include "includeAll.h"

// Factory to create entities by type using variadic templates
class EntityFactory {
public:
    enum Type {                       // Supported entity types
        brickBlock,
        groundBlock,
        questionBlock,
        player,
        turtle
    };

    EntityFactory() = default;        // Default constructor

    // Create and return a shared_ptr to an Entity of the requested type
    template<typename... Args>
    static std::shared_ptr<Entity> createEntity(Type type, Args &&... args) {
        if (type == brickBlock)
            return std::make_shared<BrickBlock>(args...);          // Create brick block
        if (type == groundBlock)
            return std::make_shared<GroundBlock>(args...);        // Create ground tile
        if (type == questionBlock)
            return std::make_shared<QuestionBlock>(args...);      // Create question block
        if (type == player)
            return std::make_shared<Player>(args...);             // Create player
        if (type == turtle)
            return std::make_shared<Turtle>(args...);             // Create turtle enemy
        throw std::invalid_argument("Invalid type");           // Error on unknown type
    }
};

#endif //ENTITYFACTORY_H