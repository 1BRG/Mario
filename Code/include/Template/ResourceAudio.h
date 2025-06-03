//
// Created by Gabriel on 5/19/2025.
//

#ifndef RESOURCEAUDIO_H
#define RESOURCEAUDIO_H
#include "ResourceManager.h"
#include "../Entities/Audio.h"

struct ResourceAudio {
    inline static ResourceManager<Audio> audio;
};

#endif //RESOURCEAUDIO_H
