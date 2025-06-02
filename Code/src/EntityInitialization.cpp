//
// Created by Gabriel on 5/20/2025.
//
#include "../include/entitati/Entity.h"

void Entity::INIT() {
    AnimationManager::animations.load("coin_idle", "../Texture/all/Coin.png", 6, 3);
    AnimationManager::animations.load("mario_idle", "../Texture/all/Mario.png", 1, 6);
    AnimationManager::animations.load("mario_run", "../Texture/all/MarioRun.png", 3, 12);
    AnimationManager::animations.load("mario_jump", "../Texture/all/MarioJumping.png", 1, 4);
    AnimationManager::animations.load("mario_skidding", "../Texture/all/MarioSkidding.png", 1, 1);


    AnimationManager::animations.load("turtle_idle", "../Texture/all/TurtleRun.png", 2, 2);
    AnimationManager::animations.load("turtle_run", "../Texture/all/TurtleRun.png", 2, 2);
    AnimationManager::animations.load("turtle_jump", "../Texture/all/TurtleRun.png", 2, 2);

    AnimationManager::animations.load("furiousRun", "../Texture/all/FuriousRunFixed.png", 1, 1);

    AnimationManager::animations.load("BrickBlock", "../Texture/all/BrickBlockBrown.png", 1, 1);

    AnimationManager::animations.load("GroundBlock", "../Texture/all/FloorTile.png", 1, 1);

    AnimationManager::animations.load("questionBlock", "../Texture/all/QuestionBlock.png", 6, 3);

    AnimationManager::animations.load("EmptyBlock", "../Texture/all/EmptyBlock.png", 1, 6);

    //AUDIO
    ResourceAudio::audio.load("coinSound", "../Sound/coin.wav", Audio::Type::SOUND);
    ResourceAudio::audio.load("marioJump", "../Sound/jump.wav", Audio::Type::SOUND);

    ResourceAudio::audio.load("kickKill", "../Sound/kickKill.wav", Audio::Type::SOUND);

    ResourceAudio::audio.load("brickDestroy", "../Sound/brickDestroy.wav", Audio::Type::SOUND);
}