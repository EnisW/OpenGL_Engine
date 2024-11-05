#include "def.h"

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
    std::string vertex_shader_source = load_shader_source("shaders/vertex/vertex_test.vert");
    const char* vertex_source = vertex_shader_source.c_str();

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
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
    std::string fragment_shader_source = load_shader_source("shaders/fragment/fragment_test.frag");
    const char* fragment_source = fragment_shader_source.c_str();
    
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);

    int fragment_success;
    char fragment_info_log[512];
    glGetProgramiv(fragment_shader, GL_COMPILE_STATUS, &fragment_success);

    if (!fragment_success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, fragment_info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fragment_info_log << std::endl;
    }

    // DEFINITON OF SHADER PROGRAM AND ATTACHING SHADERS VERTEX AND FRAGMENT THEN LINKING
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int shader_program_success;
    char shader_program_info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_program_success);

    if(!shader_program_success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, shader_program_info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << shader_program_info_log << std::endl;
    }

    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);



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