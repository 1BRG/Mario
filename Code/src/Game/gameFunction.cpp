//
// Created by Gabriel on 4/2/2025.
//

#include "../../include/game/gameFunction.h"

int ct = 0;
game *game::instance = nullptr;

// Return or create singleton instance
game *game::GetInstance() {
    if (instance == nullptr) {
        instance = new game();
    }
    return instance;
}

// Placeholder to invalidate game on player death
void game::setValid() {
    ///daca player.health <= 0 false
}

// Main game loop: window init, level load, input, update, render
void game::StartGameLoop() {
    InitAudioDevice();
    InitWindow(screenWidth, screenHeight, "Hello World");
    SetTargetFPS(144);
    bgMusic = ResourceAudio::audio.load("themeSound", "../Sound/ThemeSong.mp3", Audio::Type::MUSIC, true);
    bgMusic->play();
    bgMusic->setVolume(0.5);
    Entity::INIT(); // Static entity init
    Texture2D bgTexture = LoadTexture("../Texture/Background1.png");
    SetTextureFilter(bgTexture, TEXTURE_FILTER_POINT);
    RenderTexture2D renderTexture = LoadRenderTexture(495, 270);
    float tileScale = (float) renderTexture.texture.width / bgTexture.width;
    float fr = 0;
    int o = 0;
    setLevel(1); // Load first level
    setEntities(); // Categorize entities
    for (const auto &c: movEnv) {
        auto aux = std::dynamic_pointer_cast<QuestionBlock>(c);
        if (aux != nullptr) {
            aux->setWorld(instance);
        }
    }
    while (!WindowShouldClose()) {
        // Game loop
        o++;
        ClearBackground(BLUE);
        setFPS(fr, o);
        if (IsKeyDown(KEY_Q)) bgMusic->pause();
        if (IsKeyDown(KEY_R)) bgMusic->resume();
        BeginTextureMode(renderTexture);
        ClearBackground(BLUE);

        // Update living entities: dt, lifetime, screen cull
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
        // Update static and movable environment similarly
        for (auto it = environment.begin(); it != environment.end();) {
            (*it)->deltaTime(fr);
            if (!(*it)->isAlive()) it = environment.erase(it);
            else ++it;
        }
        for (auto it = movEnv.begin(); it != movEnv.end();) {
            (*it)->deltaTime(fr);
            if (!(*it)->isAlive()) {
                deleteEntity(*it);
                it = movEnv.erase(it);
            } else ++it;
        }

        // Collision & movement for living entities
        for (const auto &entity: entities) bottomCollision(entity);
        for (const auto &entity: entities) entity->moveToTarget();
        for (const auto &entity: entities) entity->update();
        collision(entities);
        for (const auto &entity: movEnv) entity->update();
        for (const auto &entity: entities) entity->moveToTarget();
        for (const auto &entity: movEnv) entity->moveToTarget();

        // Camera tracking on first entity
        if (entities.front()->coord_x() - cameraX > 495 * 0.5f) {
            cameraX += entities.front()->coord_x() - cameraX - 495 * 0.5f;
        }

        // Draw parallax background tiles
        Rectangle srcRec = {0, 0, (float) bgTexture.width, (float) bgTexture.height};
        float tileW = bgTexture.width * tileScale;
        float tileH = bgTexture.height * tileScale;
        float scrollX = fmod(cameraX, tileW);
        if (scrollX < 0) scrollX += tileW;
        for (float x = -scrollX; x < renderTexture.texture.width + tileW; x += tileW)
            for (float y = -tileH; y < renderTexture.texture.height + tileH; y += tileH) {
                Rectangle dstRec = {x, y, tileW, tileH};
                DrawTexturePro(bgTexture, srcRec, dstRec, {0, 0}, 0, WHITE);
            }
        draw(); // Draw all entities
        EndTextureMode();

        // Final draw to screen with FPS and score overlay
        BeginDrawing();
        DrawTexturePro(renderTexture.texture, {0, 0, 495, -270}, {0, 0, 1920, 1080}, {0, 0}, 0,WHITE);
        DrawText(TextFormat("%.1f", GetFPS()), 10, 15, 25,GREEN);
        std::string Score = "Score: ";
        Score += std::to_string(score->getScore());
        DrawText(Score.c_str(), 10, 50, 40,WHITE);
        EndDrawing();
    }
    CloseAudioDevice();
}
