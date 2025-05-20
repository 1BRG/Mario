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
    InitAudioDevice();
    bgMusic = ResourceAudio::audio.load("themeSound", "../Sound/ThemeSong.mp3", Audio::Type::MUSIC, true);
    bgMusic->play();
    bgMusic->setVolume(0.5);
    InitWindow(screenWidth, screenHeight, "Hello World");
    Entity::INIT();
    Texture2D bgTexture = LoadTexture("../Texture/image.jpg");
    SetTargetFPS(144);
    //   Texture2D texture = LoadTexture("../Texture/fundal.png");
    ClearBackground(GREEN);
    setLevel(1);
    setEntities();
    float fr = 0;
    int o = 0;
    RenderTexture2D renderTexture = LoadRenderTexture(495, 270);
    while (!WindowShouldClose()) {
        o++;
        ClearBackground(BLUE);
        setFPS(fr, o);
        // fr = 0.0056;
        bgMusic->update();
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
        for (auto it = movEnv.begin(); it != movEnv.end(); ) {
            (*it)->deltaTime(fr);
            if (!(*it)->isAlive()) {
                deleteEntity(*it);
                it = movEnv.erase(it);
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
        for (const auto &entity: movEnv)
            // if (inScreenEntity(entity))
                entity->update();
       //DrawPixels()

        for (const auto &entity: entities)
            //  if (inScreenEntity(entity))
            try {
                entity->moveToTarget();
            } catch (TextureException &txt) {
                std::cout << txt.what() << std::endl;
                exit(0);
            }
        for (const auto &entity: movEnv)
            entity->moveToTarget();

        if (entities.front()->coord_x() - cameraX > 495 * 1. / 2) {
            float dec = entities.front()->coord_x() - cameraX - 495 * 1. / 2;
            cameraX += dec;
        }
        //  for (const auto& entity : entities)
        //            std::cout << (*entity);
        for (int x = -bgTexture.width; x < screenWidth + bgTexture.width; x += bgTexture.width)
        {
            for (int y = -bgTexture.height; y < screenHeight + bgTexture.height; y += bgTexture.height)
            {
                DrawTexture(bgTexture, x * 1. - cameraX, y, WHITE);
            }
        }
        draw();
        EndTextureMode();
        // cout << GetFPS() << "FPS" << endl;
        BeginDrawing();
        DrawTexturePro(renderTexture.texture, {0, 0, 495, -270}, {0, 0, 1920, 1080}, {0, 0}, 0, WHITE);
        EndDrawing();
    }
    CloseAudioDevice();
}