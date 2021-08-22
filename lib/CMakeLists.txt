project(lib)

set(CMAKE_CXX_STANDARD 20)

add_library(
        lib SHARED
        exception.cpp
        todo.cpp
        io.cpp
        stb_image.cpp
        gl_error_check.cpp
)
