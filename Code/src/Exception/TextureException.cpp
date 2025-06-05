
//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/Exception/TextureException.h"

// Initialize exception message for missing texture
TextureException::TextureException(const std::string &txt)
    : BaseException("Texture: " + txt + " doesn't exist!") {
}
