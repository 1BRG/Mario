//
// Created by Gabriel on 5/2/2025.
//

#include "../../include/exceptii/BaseException.h"

BaseException::BaseException(const std::string &txt) : mesaj(txt){

}

const char* BaseException::what() const throw() {
    return mesaj.c_str();
}
