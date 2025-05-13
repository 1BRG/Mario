//
// Created by Gabriel on 4/2/2025.
//

#include "../../include/game/gameFunction.h"
#include <iostream>

int ct = 0;
game *game::instance = nullptr;

game *game::GetInstance() {
    if (instance == nullptr) {
        instance = new game();
    }
    return instance;
}

void game::setValid() {
    ///daca player.health <= 0 false
}


void game::StartGameLoop() {
    InitWindow(screenWidth, screenHeight, "Hello World");
    SetTargetFPS(144);
    //   Texture2D texture = LoadTexture("../Texture/fundal.png");
    ClearBackground(GREEN);
    Brick::InitStatics();
    setLevel(1);
    setEntities();
    float fr = 0;
    int o = 0;
    //  ToggleFullscreen();
    ToggleFullscreen();
    RenderTexture2D renderTexture = LoadRenderTexture(256, 250);
    while (!WindowShouldClose()) {
        o++;
        ClearBackground(BLUE);
        fr = GetFrameTime();
        try {
            if (fr <= 0.20)
                throw(fr);
            if (o >= 10) throw(FpsException());
            throw std::string("continua");
        } catch (FpsException &e) {
            std::cout << e.what() << std::endl;
            //exit(0);
        }
        catch (float e) {
            fr = e;
        }
        catch (...) {
            fr = 0;
        }
        // fr = 0.0056;
        // dt = 0.0096;

        BeginTextureMode(renderTexture);
        ClearBackground(BLUE);
        //DrawTexturePro(texture, {0,0,float(texture.width), float(texture.height)}, {0, 0, screenWidth, screenHeight}, {0, 0}, 0, WHITE);
        for (auto it = entities.begin(); it != entities.end();) {
            (*it)->deltaTime(fr);
            if (!(*it)->isAlive()) {
                deleteEntity(*it);
                it = entities.erase(it);
            } else if (inScreenEntity(*it)) {
                (*it)->setLastY();
                ++it;
            } else ++it;
        }
        for (const auto &entity: entities)
            //if (inScreenEntity(entity))
            bottomCollision(entity);
        for (const auto &entity: entities)
        // if (inScreenEntity(entity))
        {
            try {
                entity->moveToTarget();
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        }
        for (const auto &entity: entities)
            // if (inScreenEntity(entity))
            entity->update();
        collision(entities);


        /*
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
        */

        for (const auto &entity: entities)
            //  if (inScreenEntity(entity))
            try {
                entity->moveToTarget();
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }


        if (entities.front()->coord_x() - cameraX > 256 * 1. / 2) {
            float dec = entities.front()->coord_x() - cameraX - 256 * 1. / 2;
            cameraX += dec;
        }
        //  for (const auto& entity : entities)
        //            std::cout << (*entity);
        draw();
        EndTextureMode();
        // cout << GetFPS() << "FPS" << endl;
        BeginDrawing();
        DrawTexturePro(renderTexture.texture, {0, 0, 256, -256}, {420, 0, 1080, 1080}, {0, 0}, 0, WHITE);
        EndDrawing();
    }
}
