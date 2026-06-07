cmake_minimum_required(VERSION 3.24)
project(5)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(5 main.cpp)

target_link_libraries(5
        glfw
        OpenGL::GL
        OpenGL::GLU
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/tekstura.tga DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/tekstura2.tga DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
