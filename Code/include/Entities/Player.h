//
// Created by Gabriel on 4/16/2025.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "Living.h"
#include "Coin.h"
#include "../Observer/ScoreManager.h"

// Player entity controlled by user, handles input and scoring
class Player : public Living {
    static std::string MarioIDLE;    // Filepath for idle animation
    static std::string MarioRUN;     // Filepath for running animation
    static std::string MarioJUMP;    // Filepath for jumping animation
    static std::string MarioSKIDDING;// Filepath for skidding animation
    bool gaveDamage{false};          // Flag if player dealt damage this frame
    std::shared_ptr<ScoreManager> score; // Observer for score updates

public:
    Player(float x, float y);         // Constructor with start position

    Player() = default;

    void handleInput();               // Poll keyboard and adjust speed/state

    void setScore(const std::shared_ptr<ScoreManager> &Score); // Attach score manager

    void update() override;           // Update movement and play sounds

    void collision(Entity &other, int direction) override; // Handle collisions

    void moveToTarget() override;     // Apply target positions to actual coords

    [[nodiscard]] Player *clone() const override; // Clone for entity factory

    Player(const Player &other) = default; // Default copy constructor
};

#endif //PLAYER_H
