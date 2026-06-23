#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include "Core/Utilities/ScopeExit.hpp"

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



int main(int argc, char* argv[])
{
    return EXIT_SUCCESS;
}
