#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string load_shader_source(const char*);
void framebuffer_size_callback(GLFWwindow*, int, int);
void process_input(GLFWwindow*);
void init_buffers(unsigned int&);