#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include "core/utilities/scope_exit.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

using GlHandle = std::uint32_t;

// static constexpr char* vshader_source = "#version 330 core\n"

const char* vertexShaderSource
    = "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

static const char* fragmentShaderSource
    = "#version 330 core\n"
      "out vec4 FragColor;"
      "void main()\n"
      "{\n"
      "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
      "}\0";



class GLContext
{
    ~GLContext() = default;
    GLContext() = default;
};

void entry()
{
    float vertices[]
        = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    int success;
    char infoLog[512] = {0};

    if(!glewInit())
        return;
    GLuint vertexBufferObject, vertexArrayObject, fragmentShader, vertexShader,
        shaderProgram;

    glGenBuffers(
        1, &vertexBufferObject); // Interesting macro, come back here later
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
    GL_STATIC_DRAW);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                    << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                    << infoLog << std::endl;
    }
}

int main(int argc, char* argv[])
{
    using namespace Core::Utilities;

    float vertices[]
        = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    SDL_GLContext maincontext;
    SDL_Window* window ;
    SDL_Event* event;
    bool running = true;
    GLuint vertexBufferObject, vertexArrayObject, fragmentShader, vertexShader,
        shaderProgram;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL window\n";
    }


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_GL_SetSwapInterval(1);

    entry();

    window = SDL_CreateWindow("Title",
        512, 512, SDL_WINDOW_OPENGL);
  
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        return EXIT_FAILURE;
    }

    maincontext = SDL_GL_CreateContext(window);
    if(!maincontext)
    {
        std::cerr << "Failed to create window\n";
        return EXIT_FAILURE;
    }


    ON_SCOPE_EXIT
    {
        SDL_GL_DestroyContext(maincontext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    };

    while(running)
    {
        while(SDL_PollEvent(event))
        {
            if (event->type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
    }

    return EXIT_SUCCESS;
}
