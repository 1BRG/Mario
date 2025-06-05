
//
// Created by Gabriel on 5/7/2025.
//

#include "../include/Entities/Animation.h"

// Constructor: load texture and populate frame rectangles
Animation::Animation(const std::string &filePath, int frameCount, float frameSpeed)
    : frameCount(frameCount), currentFrame(0), frameSpeed(frameSpeed), elapsedTime(0.0f) {
    texture = LoadTexture(filePath.c_str());       // Load sprite sheet
    if (texture.id == 0)
        throw TextureException(filePath);          // Error if missing
    float frameWidth = static_cast<float>(texture.width) / frameCount;
    float frameHeight = static_cast<float>(texture.height);
    frames.reserve(frameCount);
    for (int i = 0; i < frameCount; ++i) {
        frames.push_back(Rectangle{i * frameWidth, 0, frameWidth, frameHeight}); // Define frame bounds
    }
}

// Unload texture resource
Animation::~Animation() {
    UnloadTexture(texture);
}

// Increment frame based on elapsed delta
void Animation::Update(float delta) {
    elapsedTime += delta;
    if (elapsedTime >= 1.0f / frameSpeed) {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount; // Loop frames
    }
}

// Draw frame, optionally flipped horizontally
void Animation::Draw(const Vector2 &position, const Color &tint, float delta, bool flipX) {
    Update(delta);                                  // Advance before drawing
    Rectangle src = frames[currentFrame];

    if (flipX) {
        src.x += src.width;
        src.width *= -1;                            // Flip source rectangle
    }
    DrawTextureRec(texture, src, position, tint);   // Render texture region
}

// Reset animation playback
void Animation::Reset() {
    currentFrame = 0;
    elapsedTime = 0.0f;
}

// Change speed at runtime
void Animation::SetSpeed(float speed) {
    frameSpeed = speed;
}

// Accessors
int Animation::GetFrameCount() const {
    return frameCount;
}

int Animation::GetCurrentFrame() const {
    return currentFrame;
}

int Animation::width() const {
    return texture.width / frameCount;
}

int Animation::height() const {
    return texture.height;
}

int Animation::GetFrameSpeed() const {
    return frameSpeed;
}
