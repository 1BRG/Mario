//
// Created by Gabriel on 5/2/2025.
//

#ifndef BASEEXCEPTION_H
#define BASEEXCEPTION_H

#include <exception>
#include <string>

// Base class for custom exceptions with message storage
class BaseException : public std::exception {
    std::string message;    // Error message description

public:
    // Construct exception with a descriptive text
    explicit BaseException(const std::string &txt);

    // Return stored message as C-string
    [[nodiscard]] const char *what() const throw() override;
};

#endif //BASEEXCEPTION_H
