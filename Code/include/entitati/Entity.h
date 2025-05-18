//
// Created by Gabriel on 4/1/2025.
//

#ifndef ENTITATI_H
#define ENTITATI_H

#include <cmath>
#include <memory>
#include <raylib.h>
#include <string>
#include <vector>
#include "../defineuri.h"
#include "../Exceptii/exceptii.h"
#include "Animation.h"

class Entity {
    struct CollisionInfo {
        float   time;       // momentul (0..1) al coliziunii în cadrul mișcării
        Vector2 normal;     // normală a feței lovite
        bool    collided;   // există coliziune în acest frame?
    };
protected:
    Vector2 velocity{0, 0};
    enum State { IDLE, RUN, JUMP, SKIDDING};

    Vector2 position;
    State state;
    Animation *animations[4];
    float dt;
    std::string texturePath;
    float coordX{0}, coordY{0}, x{0}, y{0};
    float targetX{0}, targetY{0};
    int health {1};
    bool moving {true};
    int damage {0};
    bool updateLeft {true}, updateRight {true}, updateTop {true}, updateBottom {true};
    Texture2D texture;
    float lastY {screenHeight};

public:
    static CollisionInfo SweptAABB(const Rectangle& moving, const Vector2& vel, const Rectangle& target);
    virtual void incomingDamage() {
    }

    virtual void collision(Entity &other, int direction) = 0;

    [[nodiscard]] std::string detectCollisionSide(const std::shared_ptr<Entity> &env, int a, int b) const;

    Entity(float x, float y, Animation *anim[4]);

    virtual void print() const;

    friend std::ostream &operator<<(std::ostream &os, const Entity &entity);

    Entity() = default;

    [[nodiscard]] static float clamp(float x, float st, float dr);

    [[nodiscard]] float coord_x() const;

    [[nodiscard]] float coord_y() const;

    [[nodiscard]] float height() const;

    [[nodiscard]] float width() const;

    [[nodiscard]] float target_x() const;

    [[nodiscard]] float target_y() const;

    [[nodiscard]] int danger() const;
    [[nodiscard]] bool isAlive() const;
    virtual void draw(float cameraX);

    void deltaTime(float deltatime);

    [[nodiscard]] virtual Entity *clone() const = 0;

    void decreaseX(float dec);

    [[nodiscard]] Rectangle getRect(int a, int b) const;

    virtual ~Entity();

    ///
    ///
};


#endif //ENTITATI_H
