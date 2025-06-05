//
// Created by Gabriel on 5/7/2025.
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>
#include <vector>
#include <string>
#include "../Exception/Exception.h"

// Handles sprite sheet animation: loading, updating, drawing frames
class Animation {
public:
    // Load texture and split into frames based on frame count
    Animation(const std::string &filePath, int frameCount, float frameSpeed);

    ~Animation();                                   // Unload texture

    void Update(float delta);                       // Advance animation by delta time

    void Draw(const Vector2 &position, const Color &tint, float delta, bool flipX); // Render current frame

    void Reset();                                   // Reset animation to first frame

    void SetSpeed(float speed);                     // Adjust playback speed

    int GetFrameCount() const;                      // Total frames in animation

    int GetCurrentFrame() const;                    // Index of current frame

    int width() const;                              // Width of each frame

    int height() const;                             // Height of each frame

    int GetFrameSpeed() const;                      // Playback speed (fps)

private:
    Texture2D texture;                              // Sprite sheet texture
    std::vector<Rectangle> frames;                  // Source rectangles per frame
    int frameCount;                                 // Number of frames
    int currentFrame;                               // Current frame index
    float frameSpeed;                               // Frames per second
    float elapsedTime;                              // Time since last frame change
};

#endif //ANIMATION_H

