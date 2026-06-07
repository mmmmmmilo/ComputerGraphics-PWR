cmake_minimum_required(VERSION 3.24)
project(4)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(4 main.cpp)

target_link_libraries(4
        glfw
        OpenGL::GL
        OpenGL::GLU
)
