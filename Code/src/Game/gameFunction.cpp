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
    InitWindow(screenWidth, screenHeight, "Hello World");
    SetTargetFPS(144);
    bgMusic = ResourceAudio::audio.load("themeSound", "../Sound/ThemeSong.mp3", Audio::Type::MUSIC, true);
    bgMusic->play();
    bgMusic->setVolume(0.5);
    Entity::INIT();
    Texture2D bgTexture = LoadTexture("../Texture/Background1.png");
    SetTextureFilter(bgTexture, TEXTURE_FILTER_POINT);
    RenderTexture2D renderTexture = LoadRenderTexture(495, 270);
    float tileScale = (float) renderTexture.texture.width / bgTexture.width;
    float fr = 0;
    int o = 0;
    setLevel(1);
    setEntities();
    for (const auto &c: movEnv) {
        auto aux = std::dynamic_pointer_cast<QuestionBlock>(c);
        if (aux != nullptr) {
            aux->setWorld(instance);
        }
    }
   // ToggleFullscreen();
    while (!WindowShouldClose()) {
        o++;
        ClearBackground(BLUE);
     //   setFPS(fr, o);
        fr = 0.0056;
        bgMusic->update();
        // dt = 0.0096;
        if (IsKeyDown(KEY_Q)) {
            bgMusic->pause();
        }
        if (IsKeyDown(KEY_R)) {
            bgMusic->resume();
        }
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
        for (auto it = environment.begin(); it != environment.end();) {
            (*it)->deltaTime(fr);
            if (!(*it)->isAlive())
                it = environment.erase(it);
            else ++it;
        }
        for (auto it = movEnv.begin(); it != movEnv.end();) {
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
        Rectangle srcRec = {0, 0, (float) bgTexture.width, (float) bgTexture.height};
        float tileW = bgTexture.width * tileScale;
        float tileH = bgTexture.height * tileScale;
        // calculăm offset-ul în spaţiul RT:
        float scrollX = fmod(cameraX, tileW);
        // ne asigurăm că scrollX e între 0 și tileW
        if (scrollX < 0) scrollX += tileW;
        // primul tile începe la -scrollX:
        for (float x = -scrollX; x < renderTexture.texture.width + tileW; x += tileW) {
            for (float y = -tileH; y < renderTexture.texture.height + tileH; y += tileH) {
                Rectangle dstRec = {
                    x,
                    y,
                    tileW,
                    tileH
                };
                DrawTexturePro(bgTexture, srcRec, dstRec, (Vector2){0, 0}, 0.0f, WHITE);
            }
        }
        draw();

        EndTextureMode();

        // cout << GetFPS() << "FPS" << endl;

        BeginDrawing();

        DrawTexturePro(renderTexture.texture, {0, 0, 495, -270}, {0, 0, 1920, 1080}, {0, 0}, 0, WHITE);
        float fps = GetFPS();
        DrawText(TextFormat("%.1f", fps), 10, 15, 25, GREEN);
        std::string Score = "Score: ";
        Score += std::to_string(score->getScore());
        DrawText(Score.c_str(), 10, 50, 40, WHITE);
        EndDrawing();
    }
    CloseAudioDevice();
}
