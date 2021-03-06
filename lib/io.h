//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_IO_H
#define OPENGL_IO_H

#include "option.hpp"
#include <string>

Option<std::string> readLine(FILE *fp);

std::string readFileToString(const char* path);

#endif //OPENGL_IO_H
