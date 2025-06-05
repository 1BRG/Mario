//
// Created by Gabriel on 5/3/2025.
//

#ifndef TEXTUREEXCEPTION_H
#define TEXTUREEXCEPTION_H

#include "BaseException.h"

// Exception thrown when a texture resource fails to load
class TextureException : public BaseException {
public:
    // Construct with texture file path; message indicates missing resource
    explicit TextureException(const std::string &txt);
};

#endif //TEXTUREEXCEPTION_H
