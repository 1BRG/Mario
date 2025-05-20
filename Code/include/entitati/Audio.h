//
// Created by Gabriel on 5/19/2025.
//

#ifndef AUDIO_H
#define AUDIO_H
#include <string>

#include "raylib.h"


class Audio {

    Sound sound;
    Music music;
    bool loop;
    float volume{1.0};
public:
    enum class Type {SOUND, MUSIC};
    Audio(const std::string &filePath, Type type, bool loop = false);
    ~Audio();
    void play();
    void stop();
    void pause();
    void resume();
    void update();
    void setVolume(float volume);

private:
    Type type;
};



#endif //AUDIO_H
