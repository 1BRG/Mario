//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/exceptii/TextureException.h"

TextureException::TextureException(const std::string &txt) : BaseException("Textura: " + txt + " nu exista!"){
}
