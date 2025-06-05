

//
// Created by Gabriel on 5/2/2025.
//

#include "../../include/Exception/BaseException.h"

// Initialize exception with given message
BaseException::BaseException(const std::string &txt) : message(txt) {
}

// Provide message for catching code
const char *BaseException::what() const throw() {
    return message.c_str();
}
