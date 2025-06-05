//
// Created by Gabriel on 5/3/2025.
//

#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include "BaseException.h"

// Exception thrown when a required file is missing or cannot be opened
class FileException : public BaseException {
public:
    // Construct with filename; message indicates missing file
    explicit FileException(const std::string &txt);
};

#endif //FILEEXCEPTION_H
