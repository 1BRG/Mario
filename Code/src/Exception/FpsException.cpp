
//
// Created by Gabriel on 5/3/2025.
//

#include "../../include/Exception/FpsException.h"

// Initialize exception indicating frame timing issue
FpsException::FpsException()
    : BaseException("Too much time between frames, possible errors!") {
}
