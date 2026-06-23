#include "core/window/window.hpp"
#include <SDL3/SDL_video.h>

namespace Core::Window 
{
    namespace Detail { }

    Window::Window(std::uint32_t width,
            std::uint32_t height,
            std::string name)
        : 
        _width(width),
        _height(height),
        _name(name)
    { 
        // This shouldn't be done by the window. 
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        }

        if (_window = SDL_CreateWindow(_name.c_str(), _width, _height, 0 ) ; !_window)
        {
            SDL_Log("SDL could not create a window! SDL error: %s\n", SDL_GetError());
        }
    }


    Window::~Window()
    {
        SDL_DestroySurface(_surface);
        _surface = nullptr;

        SDL_DestroyWindowSurface(_window);
        _window = nullptr;

        SDL_Quit(); // this should not be handled by the window.
    }

    void Window::close()
    {
    }
}
