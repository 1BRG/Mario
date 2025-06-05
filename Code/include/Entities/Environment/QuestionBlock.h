
//
// Created by Gabriel on 5/14/2025.
//

#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H

#include "MovebleEnvironment.h"
#include "../../game/gameFunction.h"
class game;

// Interactive question block that spawns a coin when hit
class QuestionBlock : public MovebleEnvironment {
    static std::string QuestionTexture;    // Path to question block texture
    static std::string EmptyBlockTexture;  // Path to empty block texture
    bool active{true};                     // Flag if block still contains an item
    game *world{};                           // Pointer to game instance for spawning entities

public:
    QuestionBlock(float dx, float dy);     // Constructor sets position and initial animation

    QuestionBlock(const QuestionBlock &other) = default; // Default copy constructor

    void setWorld(game *g);                // Assign game world context

    void collision(Entity &other, int direction) override; // Handle block hit from below

    void update() override;                // Update state and animation each frame

    [[nodiscard]] QuestionBlock *clone() const override; // Clone block for level loading

    ~QuestionBlock() override;             // Destructor cleans up
};

#endif //QUESTIONBLOCK_H
