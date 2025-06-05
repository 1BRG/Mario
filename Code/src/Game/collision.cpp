//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/game/gameFunction.h"

 // Check top-side collisions and resolve
void game::topCollision(const std::shared_ptr<Living> &entity) const {
    for (const auto &env: environment) if (entity->topCollision(env)) entity->collision(*env, -1);
    for (const auto &env: entities) if (entity->topCollision(env) && env != entity)
        entity->collision(*env, -1), env->collision(*entity, 1);
    for (const auto &env: movEnv) if (entity->topCollision(env))
        entity->collision(*env, -1), env->collision(*entity, 1);
}

// Bottom-side collisions and resolve
void game::bottomCollision(const std::shared_ptr<Living> &entity) const {
    for (auto env: environment) if (entity->bottomCollision(env)) entity->collision(*env, 1);
    for (const auto &env: entities) if (entity->bottomCollision(env) && entity != env)
        entity->collision(*env, 1), env->collision(*entity, -1);
    for (const auto &env: movEnv) if (entity->bottomCollision(env))
        entity->collision(*env, 1), env->collision(*entity, -1);
}

// Left-side collisions
void game::leftCollision(const std::shared_ptr<Living> &entity) const {
    for (const auto &env: environment) if (entity->leftCollision(env)) entity->collision(*env, -2);
    for (const auto &env: entities) if (entity->leftCollision(env) && entity != env)
        entity->collision(*env, -2), env->collision(*entity, 2);
    for (const auto &env: movEnv) if (entity->leftCollision(env))
        entity->collision(*env, -2), env->collision(*entity, 2);
}

// Right-side collisions
void game::rightCollision(const std::shared_ptr<Living> &entity) const {
    for (const auto &env: environment) if (entity->rightCollision(env)) entity->collision(*env, 2);
    for (const auto &env: entities) if (entity->rightCollision(env) && entity != env)
        entity->collision(*env, 2), env->collision(*entity, -2);
    for (const auto &env: movEnv) if (entity->rightCollision(env))
        entity->collision(*env, 2), env->collision(*entity, -2);
}

// Global collision check helper
void game::collision(const std::list<std::shared_ptr<Living> > &entities) {
    game *currentGame = GetInstance();
    for (const auto &entity: entities) {
        currentGame->leftCollision(entity);
        currentGame->rightCollision(entity);
        currentGame->topCollision(entity);
        currentGame->bottomCollision(entity);
    }
}
