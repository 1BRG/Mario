//
// Created by Gabriel on 5/2/2025.
//

#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>
#include <string>

class BaseException : public std::exception {
  std::string mesaj;
public:
    explicit BaseException(const std::string &txt);

  const char* what() const throw() override;
};



#endif //BASEEXCEPTION_H
