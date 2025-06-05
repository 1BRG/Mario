//
// Created by Gabriel on 5/19/2025.
//

#ifndef AUDIO_H
#define AUDIO_H
#include <string>
#include "raylib.h"

// Wrapper for playing sounds and music using raylib
class Audio {

    Sound sound;              // raylib sound resource
    Music music;              // raylib music stream resource
    bool loop;                // Looping enabled for music
    float volume{1.0};        // Playback volume
public:
    enum class Type {SOUND, MUSIC};  // Media type for resource

    // Load sound or music from file, optional looping for music
    Audio(const std::string &filePath, Type type, bool loop = false);
    ~Audio();                         // Unload resources on destruction

    void play();                      // Start playback
    void stop();                      // Stop playback
    void pause();                     // Pause playback
    void resume();                    // Resume after pause
    void update();                    // Update streaming music buffer
    void setVolume(float volume);     // Adjust playback volume

private:
    Type type;                        // Indicates SOUND or MUSIC
};

#endif //AUDIO_H