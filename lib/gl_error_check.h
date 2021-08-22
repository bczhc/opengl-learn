//
// Created by bczhc on 8/22/21.
//

#ifndef OPENGL_GL_ERROR_CHECK_CALL_H
#define OPENGL_GL_ERROR_CHECK_CALL_H

#include <GL/glew.h>
#include "types.h"

#define GL_CALL(x) glClearError(); \
    x;                            \
    if (glCheckError(__FILE__, __LINE__, #x)) {          \
        abort();                   \
    }

void glClearError();

void glLogError(GLenum error, const char *file, u32 line, const char *lineCode);

bool glCheckError(const char *file, u32 line, const char *lineCode);

#endif //OPENGL_GL_ERROR_CHECK_CALL_H
