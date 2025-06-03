//
// Created by Gabriel on 5/14/2025.
//

#ifndef QUESTIONBLOCK_H
#define QUESTIONBLOCK_H

#include "MovebleEnvironment.h"
#include "../../game/gameFunction.h"
class game;

class QuestionBlock : public MovebleEnvironment {
    static std::string QuestionTexture;
    static std::string EmptyBlockTexture;
    bool active{true};
    game *world;

public:
    QuestionBlock(float dx, float dy);

    QuestionBlock(const QuestionBlock &other) = default;

    void setWorld(game *g);

    void collision(Entity &other, int direction) override;

    void update() override;

    [[nodiscard]] QuestionBlock *clone() const override;

    ~QuestionBlock() override;
};


#endif //QUESTIONBLOCK_H
