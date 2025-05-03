//
// Created by Gabriel on 5/3/2025.
//
#include "../../include/game/gameFunction.h"

bool game::inScreenEntity(std::shared_ptr<Entity> entity) const {
    if (entity->coord_x() <= -entity->width() - cameraX || entity->coord_x() - cameraX >= screenWidth
    || entity->coord_y() < -entity->height() || entity->coord_y() > screenHeight)
        return false;
    return true;
}

void game::draw() const
{
    game* currentGame = GetInstance();
    for (const auto& entitate: environment)
        if (currentGame->inScreenEntity(entitate)) {
            entitate->draw(cameraX);
        }
    for (const auto& entitate: entities) {
        if (currentGame->inScreenEntity(entitate))
            entitate->draw(cameraX);
    }
}

//Nefolosite:
void game::insertEntity(const std::shared_ptr<Entity> &entity)
{
    int yy = entity->coord_y(), xx = entity->coord_x();
    for (int i = yy; i < yy + entity->height() && i < screenHeight - 1; i++)
        for (int j = xx; j < xx + entity->width() && j < screenWidth - 1; j++)
            grid[i][j] = entity;
}

void game::deleteEntity(const std::shared_ptr<Entity> &entity)
{
    int yy = entity->coord_y(), xx = entity->coord_x();
    for (int i = yy; i < yy + entity->height() && i < screenHeight - 1; i++)
        for (int j = xx; j < xx + entity->width() && j < screenWidth - 1; j++)
            grid[i][j] = nullptr;
}
