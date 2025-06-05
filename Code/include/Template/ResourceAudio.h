
//
// Created by Gabriel on 5/19/2025.
//

#ifndef RESOURCEAUDIO_H
#define RESOURCEAUDIO_H

#include "ResourceManager.h"
#include "../Entities/Audio.h"

// Global access point for Audio resources
struct ResourceAudio {
    inline static ResourceManager<Audio> audio;        // Manager for Audio objects
};

#endif //RESOURCEAUDIO_H
