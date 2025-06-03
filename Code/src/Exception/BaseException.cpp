//
// Created by Gabriel on 5/2/2025.
//

#include "../../include/Exception/BaseException.h"

BaseException::BaseException(const std::string &txt) : message(txt) {
}

const char *BaseException::what() const throw() {
    return message.c_str();
}
