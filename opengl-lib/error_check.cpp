//
// Created by bczhc on 8/22/21.
//

#include "error_check.h"
#include <iostream>

using namespace std;

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void glLogError(GLenum error, const char *file, u32 line, const char *lineCode) {
    cout << "[OpenGL Error] (" << error << ") " << file << ' ' << line << ' ' << lineCode << endl;
}

bool glCheckError(const char *file, u32 line, const char *lineCode) {
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        glLogError(error, file, line, lineCode);
        return true;
    }
    return false;
}