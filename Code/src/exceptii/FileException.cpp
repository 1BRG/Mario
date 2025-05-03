//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/exceptii/FileException.h"

FileException::FileException(const std::string &txt) : BaseException("Fisierul: " + txt + " nu exista!") {

}
