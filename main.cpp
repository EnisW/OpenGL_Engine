#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int, int);
void process_input(GLFWwindow*);
void init_buffers(unsigned int&);

const char* vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learning OpenGL", NULL, NULL);

    if(!window) 
    {
       std::cout << "Failed to start OpenGL Window!" << std::endl; 
       glfwTerminate();
       return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {   
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
    }

    unsigned int VBO;
    init_buffers(VBO);


    // DEFINITION OF VERTEX SHADER AND COMPILING
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    int vertex_success;
    char vertex_info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_success);

    if (!vertex_success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, vertex_info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertex_info_log << std::endl;
    }

    // DEFINITION OF FRAGMENT SHADER AND COMPILING
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    int fragment_success;
    char fragment_info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_success);

    if (!fragment_success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, fragment_info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragment_info_log << std::endl;
    }
    
    


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window); // input function -- if user press esc key, the window will be close

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
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