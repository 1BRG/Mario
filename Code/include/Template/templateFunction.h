//
// Created by Gabriel on 5/18/2025.
//

#ifndef TEMPLATEFUNCTION_H
#define TEMPLATEFUNCTION_H
template<typename T>
T clamp(T v, T lo, T hi) {
    return (v < lo) ? lo : (v > hi) ? hi : v;
}
#endif //TEMPLATEFUNCTION_H
