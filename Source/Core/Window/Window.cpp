#include "Core/Window/Window.hpp"
#include <SDL3/SDL_video.h>

namespace Core::Window 
{
    namespace Detail { }

    Window::Window(std::uint32_t width,
            std::uint32_t height,
            std::string name)
        : 
        width(width),
        height(height),
        name(name)
    { 
        // This shouldn't be done by the window. 
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        }

        if (window = SDL_CreateWindow(name.c_str(), width, height, 0 ) ; !window)
        {
            SDL_Log("SDL could not create a window! SDL error: %s\n", SDL_GetError());
        }
    }


    Window::~Window()
    {
        SDL_DestroySurface(surface);
        surface = nullptr;

        SDL_DestroyWindowSurface(window);
        window = nullptr;

        SDL_Quit(); // this should not be handled by the window.
    }

    void Window::Close()
    {
    }
}
