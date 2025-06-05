//
// Created by Gabriel on 4/2/2025.
//

#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include "../defineuri.h"
#include "../Entities/includeAll.h"

// Singleton managing game initialization, loop, rendering, entity collision and level setup
class game {
    std::shared_ptr<ScoreManager> score; // Score observer
    std::shared_ptr<Audio> bgMusic; // Background music player
    bool valid = true; // Game state flag
    float cameraX{0}, cameraY{0}; // Camera position for scrolling
    std::shared_ptr<Entity> grid[screenHeight][screenWidth]; // Spatial grid (unused)
    std::list<std::shared_ptr<Living> > entities; // Active living entities (player, enemies)
    std::list<std::shared_ptr<Entity> > level; // All loaded entities for level
    std::list<std::shared_ptr<Entity> > environment; // Static environment elements
    std::list<std::shared_ptr<MovebleEnvironment> > movEnv; // Dynamic environment elements
    static game *instance; // Singleton instance

    game() { score = std::make_shared<ScoreManager>(); }; // Private constructor

public:
    static game *GetInstance(); // Access singleton

    void setLevel(int k); // Load level from file
    void setEntities(); // Categorize loaded entities
    static void setValid(); // Invalidate game (e.g., on player death)

    bool inScreenEntity(const std::shared_ptr<Entity> &entity) const; // Check on-screen
    void insertEntity(const std::shared_ptr<Entity> &entity); // Add to environment
    void deleteEntity(const std::shared_ptr<Entity> &entity); // Remove from grid

    // Collision checks per side for a living entity
    void topCollision(const std::shared_ptr<Living> &entity) const;

    void bottomCollision(const std::shared_ptr<Living> &entity) const;

    void rightCollision(const std::shared_ptr<Living> &entity) const;

    void leftCollision(const std::shared_ptr<Living> &entity) const;

    static void collision(const std::list<std::shared_ptr<Living> > &entities); // Global collision handling

    static void setFPS(float &fr, int o); // Frame timing and exception handling

    void StartGameLoop(); // Initialize window, load resources, main loop
    void draw(); // Render entities and environment
};

#endif //GAMEFUNCTION_H
