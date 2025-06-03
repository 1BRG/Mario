//
// Created by Gabriel on 5/7/2025.
//

#include "../include/Entities/Animation.h"

Animation::Animation(const std::string &filePath, int frameCount, float frameSpeed)
    : frameCount(frameCount), currentFrame(0), frameSpeed(frameSpeed), elapsedTime(0.0f) {
    texture = LoadTexture(filePath.c_str());
    if (texture.id == 0)
        throw TextureException(filePath);
    float frameWidth = static_cast<float>(texture.width) / frameCount;
    float frameHeight = static_cast<float>(texture.height);
    frames.reserve(frameCount);
    for (int i = 0; i < frameCount; ++i) {
        frames.push_back(Rectangle{i * frameWidth, 0, frameWidth, frameHeight});
    }
}

Animation::~Animation() {
    UnloadTexture(texture);
}

void Animation::Update(float delta) {
    elapsedTime += delta;
    if (elapsedTime >= 1.0f / frameSpeed) {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % frameCount;
    }
}

void Animation::Draw(const Vector2 &position, const Color &tint, float delta, bool flipX) {
    Update(delta);
    Rectangle src = frames[currentFrame];

    if (flipX) {
        src.x += src.width;
        src.width *= -1;
    }
    DrawTextureRec(texture, src, position, tint);
}

void Animation::Reset() {
    currentFrame = 0;
    elapsedTime = 0.0f;
}

void Animation::SetSpeed(float speed) {
    frameSpeed = speed;
}

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
