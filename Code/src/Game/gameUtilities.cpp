//
// Created by Gabriel on 5/3/2025.
//
#include "../../include/game/gameFunction.h"


// Screen culling test
bool game::inScreenEntity(const std::shared_ptr<Entity> &entity) const {
    if (entity->coord_x() <= -entity->width() - cameraX || entity->coord_x() - cameraX >= screenWidth
        || entity->coord_y() < -entity->height() || entity->coord_y() > screenHeight)
        return false;
    return true;
}

// Draw all on-screen entities with camera offset
void game::draw() {
    game *currentGame = GetInstance();
    for (const auto &entity: environment) if (currentGame->inScreenEntity(entity)) entity->draw(cameraX);
    for (const auto &entity: entities) if (currentGame->inScreenEntity(entity)) entity->draw(cameraX);
    for (const auto &entity: movEnv) if (currentGame->inScreenEntity(entity)) entity->draw(cameraX);
}

// Add entity to environment list
void game::insertEntity(const std::shared_ptr<Entity> &entity) {
    environment.push_back(entity);
}

// Remove entity from spatial grid (unused)
void game::deleteEntity(const std::shared_ptr<Entity> &entity) {
    int yy = entity->coord_y(), xx = entity->coord_x();
    for (int i = yy; i < yy + entity->height() && i < screenHeight - 1; i++)
        for (int j = xx; j < xx + entity->width() && j < screenWidth - 1; j++)
            grid[i][j] = nullptr;
}

// Frame timing: get delta, throw or catch exceptions
void game::setFPS(float &fr, int o) {
    fr = GetFrameTime();
    try {
        if (fr <= 0.20) throw fr;
        if (o >= 10) throw(FpsException());
        throw std::string("continua");
    } catch (FpsException &e) {
        std::cout << e.what() << std::endl;
    } catch (float e) {
        fr = e;
    } catch (...) {
        fr = 0;
    }
} /*
void DrawPixels()
{
        for (int i = 0; i < screenHeight; i ++) {
            for (int j = 0; j < screenWidth; j++) {
                if (grid[i][j] != nullptr)
                    DrawPixel(j, i, BLACK);
                else DrawPixel(j, i, GREEN);
                if (grid[i][j] != nullptr) {
                    if ((i - grid[i][j]->coord_y() >= 0 && i - grid[i][j]->coord_y() < 10) && (j - grid[i][j]->coord_x() >= 0 && j - grid[i][j]->coord_x() < 10)) {
                        DrawPixel(j, i, RED);
                    }
                }
                //   else cout << " ";
            }
            cout << endl;
        }
        }*/
