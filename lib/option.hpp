//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_OPTION_H
#define OPENGL_OPTION_H

#include "exception.h"
#include <iostream>

class GetNoneException : Exception {
public:
    explicit GetNoneException(const std::string &message) : Exception(message) {}
};

template<typename T>
class Option {
private:
    T value;
    bool none = false;

    explicit Option() {
        this->none = true;
    }
public:
    explicit Option(const T &value) {
        this->value = value;
    }

    bool isNone() const {
        return none;
    }

    T get() const {
        if (none) {
            throw GetNoneException("Get a none value");
        }
        return value;
    }

    static Option<T> getNone() {
        return Option<T>();
    }
};

#endif //OPENGL_OPTION_H
