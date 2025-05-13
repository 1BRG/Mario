//
// Created by Gabriel on 5/3/2025.
//

#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include "BaseException.h"


class FileException : public BaseException {
public:
    explicit FileException(const std::string &txt);
};


#endif //FILEEXCEPTION_H
