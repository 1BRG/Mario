//
// Created by Gabriel on 5/3/2025.
//

#ifndef FPSEXCEPTION_H
#define FPSEXCEPTION_H

#include "BaseException.h"

class FpsException : public BaseException {
 public:
 explicit FpsException(const std::string &txt);
};



#endif //FPSEXCEPTION_H
