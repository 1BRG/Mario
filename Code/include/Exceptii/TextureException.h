//
// Created by Gabriel on 5/3/2025.
//

#ifndef TEXTUREEXCEPTION_H
#define TEXTUREEXCEPTION_H

#include "BaseException.h"

class TextureException : public BaseException {

public:
    explicit TextureException(const std::string &txt);
};



#endif //TEXTUREEXCEPTION_H
