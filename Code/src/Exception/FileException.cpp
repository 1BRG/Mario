//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/Exception/FileException.h"

FileException::FileException(const std::string &txt) : BaseException("File: " + txt + " doesn't exist!") {
}
