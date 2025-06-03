//
// Created by Gabriel on 5/7/2025.
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>
#include <vector>
#include <string>
#include "../Exception/Exception.h"

class Animation {
public:
    // Constructor: load spritesheet and split into frames
    Animation(const std::string &filePath, int frameCount, float frameSpeed);

    ~Animation();

    // Update animation (delta time in seconds)
    void Update(float delta);

    // Draw current frame at position
    void Draw(const Vector2 &position, const Color &tint, float delta, bool flipX);

    // Reset to first frame
    void Reset();

    // Change animation speed
    void SetSpeed(float speed);

    // Getters
    int GetFrameCount() const;

    int GetCurrentFrame() const;

    int width() const;

    int height() const;

    int GetFrameSpeed() const;

private:
    Texture2D texture;
    std::vector<Rectangle> frames;
    int frameCount;
    int currentFrame;
    float frameSpeed; // frames per second
    float elapsedTime; // time accumulator
};


#endif //ANIMATION_H
