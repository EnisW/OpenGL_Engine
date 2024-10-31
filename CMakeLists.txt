cmake_minimum_required(VERSION 3.10)
project(OpenGL_Engine)

set(CMAKE_CXX_STANDARD 17)


file(GLOB SOURCES "*.cpp")

add_executable(OpenGL_Engine ${SOURCES})
