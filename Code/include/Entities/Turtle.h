//
// Created by Gabriel on 4/16/2025.
//

#ifndef TURTLE_H
#define TURTLE_H
#include "Enemy.h"

// Turtle enemy with behavior change on damage
class Turtle : public Enemy {
    static std::string TurtleRUN;    // Path for normal running animation
    static std::string FuriousRUN;   // Path for enraged running animation
    static int isd;                  // Static counter for unique IDs
    int local_id = ++isd;            // Instance-specific identifier

public:
    Turtle(float x, float y);        // Constructor setting position and initial state

    void collision(Entity &other, int direction) override; // Custom collision handling

    void update() override;          // Update movement each frame

    void moveToTarget() override;    // Apply movement and handle enraged state

    [[nodiscard]] Turtle *clone() const override; // Clone for spawning

    Turtle &operator=(const Turtle &other); // Assignment copies textures and stats

    Turtle(const Turtle &other) = default;
};

#endif //TURTLE_H
