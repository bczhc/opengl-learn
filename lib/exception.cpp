//
// Created by bczhc on 8/21/21.
//

#include "exception.h"

const char *Exception::what() const noexcept {
    return this->message.c_str();
}

IOException::IOException(const std::string &message) : Exception(message) {}
