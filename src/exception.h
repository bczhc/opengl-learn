//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_EXCEPTION_H
#define OPENGL_EXCEPTION_H

#include <exception>
#include <string>

class Exception : std::exception {
private:
    std::string message;

public:
    [[nodiscard]] const char *what() const noexcept override;

    explicit Exception(const std::string &message) {
        this->message = message;
    }
};

class IOException : public Exception {
public:
    explicit IOException(const std::string &message);
};

#endif //OPENGL_EXCEPTION_H
