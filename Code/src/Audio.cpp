

//
// Created by Gabriel on 5/19/2025.
//

#include "../include/Entities/Audio.h"

// Load appropriate resource based on type
Audio::Audio(const std::string &filePath, Type type, bool loop): type(type), loop(loop) {
    if (type == Type::SOUND) {
        sound = LoadSound(filePath.c_str());      // Load WAV/OGG as sound
    } else {
        music = LoadMusicStream(filePath.c_str()); // Load streamable music
        music.looping = loop;                      // Set looping flag
    }
}

// Play sound or music
void Audio::play() {
    if (type == Type::SOUND) {
        PlaySound(sound);
    } else {
        PlayMusicStream(music);
    }
}

// Pause playback
void Audio::pause() {
    if (type == Type::SOUND) {
        PauseSound(sound);
    } else {
        PauseMusicStream(music);
    }
}

// Resume playback
void Audio::resume() {
    if (type == Type::SOUND) {
        ResumeSound(sound);
    } else {
        ResumeMusicStream(music);
    }
}

// Update music stream each frame to avoid stalling
void Audio::update() {
    if (type == Type::MUSIC) {
        UpdateMusicStream(music);
    }
}

// Stop playback immediately
void Audio::stop() {
    if (type == Type::SOUND) {
        StopSound(sound);
    } else {
        StopMusicStream(music);
    }
}

// Set volume for sound or music
void Audio::setVolume(float volume) {
    this->volume = volume;
    if (type == Type::SOUND) {
        SetSoundVolume(sound, volume);
    } else {
        SetMusicVolume(music, volume);
    }
}

// Unload resources when Audio object destroyed
Audio::~Audio() {
    if (type == Type::SOUND) {
        UnloadSound(sound);
    } else {
        UnloadMusicStream(music);
        CloseAudioDevice();     // Close audio device on music unload
    }
}
