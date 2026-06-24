#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include "Core/Utilities/ScopeExit.hpp"
#include "Runtime/Vulkan/VulkanCore.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

using GlHandle = std::uint32_t;

// static constexpr char* vshader_source = "#version 330 core\n"

[[maybe_unused]]
const char* vertexShaderSource
    = "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";

[[maybe_unused]]
static const char* fragmentShaderSource
    = "#version 330 core\n"
      "out vec4 FragColor;"
      "void main()\n"
      "{\n"
      "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
      "}\0";



int main( int argc, const char* argv[])
{
    SDL_Window* window = nullptr; 
    SDL_Event event; 
    bool running = true; 


    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL window\n";
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Vulkan Tutorial", 1280, 720, NULL);
    if (!window)
    {
        std::cerr << "Failed to create SDL window\n";
        return EXIT_FAILURE;
    }

    Runtime::Vulkan::VulkanCore vkCoreInstance; // Calls default ctor

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
    }

    ON_SCOPE_EXIT
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
    };

    return EXIT_SUCCESS;
}
