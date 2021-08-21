//
// Created by bczhc on 8/21/21.
//

#include <GL/glew.h>
#include <iostream>
#include "def.h"

using namespace std;

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#define GL_CALL(x) glClearError(); \
    x;                            \
    if (glCheckError(__FILE__, __LINE__, #x)) {          \
        abort();                   \
    }

void glClearError();

void glLogError(GLenum error, const char *file, u32 line, const char *lineCode);

bool glCheckError(const char *file, u32 line, const char *lineCode);

#endif //OPENGL_RENDERER_H
