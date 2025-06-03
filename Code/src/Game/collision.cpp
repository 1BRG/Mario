//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/game/gameFunction.h"

void game::topCollision(const std::shared_ptr<Living> &entity) const {
    for (const auto &env: environment) {
        if (entity->topCollision(env))
            entity->collision(*env, -1);
    }
    for (const auto &env: entities) {
        if (entity->topCollision(env) && env != entity)
            entity->collision(*env, -1), env->collision(*entity, 1);
    }
    for (const auto &env: movEnv) {
        if (entity->topCollision(env))
            entity->collision(*env, -1), env->collision(*entity, 1);
    }
}

void game::bottomCollision(const std::shared_ptr<Living> &entity) const {
    for (auto env: environment) {
        if (entity->bottomCollision(env))
            entity->collision(*env, 1);
    }
    for (const auto &env: entities) {
        if (entity->bottomCollision(env) && entity != env)
            entity->collision(*env, 1), env->collision(*entity, -1);
    }
    for (const auto &env: movEnv) {
        if (entity->bottomCollision(env))
            entity->collision(*env, 1), env->collision(*entity, -1);
    }
}

void game::leftCollision(const std::shared_ptr<Living> &entity) const {
    for (const auto &env: environment) {
        if (entity->leftCollision(env))
            entity->collision(*env, -2);
    }
    for (const auto &env: entities) {
        if (entity->leftCollision(env) && entity != env)
            entity->collision(*env, -2), env->collision(*entity, 2);
    }
    for (const auto &env: movEnv) {
        if (entity->leftCollision(env))
            entity->collision(*env, -2), env->collision(*entity, 2);
    }
}

void game::rightCollision(const std::shared_ptr<Living> &entity) const {
    for (const auto &env: environment) {
        if (entity->rightCollision(env))
            entity->collision(*env, 2);
    }
    for (const auto &env: entities) {
        if (entity->rightCollision(env) && entity != env)
            entity->collision(*env, 2), env->collision(*entity, -2);
    }
    for (const auto &env: movEnv) {
        if (entity->rightCollision(env))
            entity->collision(*env, 2), env->collision(*entity, -2);
    }
}

void game::collision(const std::list<std::shared_ptr<Living> > &entities) {
    game *currentGame = GetInstance();
    for (const auto &entity: entities) {
        //if (currentGame->inScreenEntity(entity)) {

        //  currentGame->deleteEntity(entity);
        currentGame->leftCollision(entity);
        currentGame->rightCollision(entity);
        currentGame->topCollision(entity);
        currentGame->bottomCollision(entity);
        //   }
        //      entity->moveToTarget();
        //    currentGame->insertEntity(entity);
    }
}
