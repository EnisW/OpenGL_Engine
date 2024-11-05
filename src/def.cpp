#include "def.h"

std::string load_shader_source(const char* filepath) {
    std::ifstream shaderFile;
    shaderFile.open(filepath);

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();

    shaderFile.close();

    return shaderStream.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void init_buffers(unsigned int &VBO)
{
    glGenBuffers(1, &VBO); // CREATING 1 VBO OBJECT
 
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // SETTING ACTIVE THE BUFFER OBJECT ()

    float vertices[] = {  // CORDINATES FOR TRIANGLE 
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // LOADING VALUES TO VBO 
}