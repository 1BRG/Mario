//
// Created by Gabriel on 5/3/2025.
//

#ifndef FPSEXCEPTION_H
#define FPSEXCEPTION_H

#include "BaseException.h"

// Exception thrown when frame timing exceeds expected threshold
class FpsException : public BaseException {
public:
    // Default constructor with predefined error message
    explicit FpsException();
};

#endif //FPSEXCEPTION_H
