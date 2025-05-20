//
// Created by Gabriel on 5/19/2025.
//

#include "../include/entitati/Audio.h"

Audio::Audio(const std::string &filePath, Type type, bool loop):type(type), loop(loop) {
    if (type == Type::SOUND) {
        sound = LoadSound(filePath.c_str());
    }
    else {
        music = LoadMusicStream(filePath.c_str());
        music.looping = loop;
    }
}

void Audio::play() {
    if (type == Type::SOUND) {
        PlaySound(sound);
    } else {
        PlayMusicStream(music);
    }
}

void Audio::pause() {
    if (type == Type::SOUND) {
        PauseSound(sound);
    } else {
        PauseMusicStream(music);
    }
}

void Audio::resume() {
    if (type == Type::SOUND) {
        ResumeSound(sound);
    } else {
        ResumeMusicStream(music);
    }
}

void Audio::update() {
    if (type == Type::MUSIC) {
        UpdateMusicStream(music);
    }
}

void Audio::stop() {
    if (type == Type::SOUND) {
        StopSound(sound);
    } else {
        StopMusicStream(music);
    }
}

void Audio::setVolume(float volume) {
    this->volume = volume;
    if (type == Type::SOUND) {
        SetSoundVolume(sound, volume);
    } else {
        SetMusicVolume(music, volume);
    }
}
Audio::~Audio() {
    if (type == Type::SOUND) {
        UnloadSound(sound);
    } else {
        UnloadMusicStream(music);
        CloseAudioDevice();
    }
}

