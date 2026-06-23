#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>

namespace Core::Window 
{

    namespace Detail 
    { 
        static  constexpr   std::uint32_t     default_width   { 640 };
        static  constexpr   std::uint32_t     default_height  { 480 };
    }

    class Window 
    {

        std::uint32_t   width;
        std::uint32_t   height;
        std::string     name;

        SDL_Surface*    surface;
        SDL_Window*     window;

        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;


    public:

        Window(std::uint32_t width = Detail::default_width,
                std::uint32_t height = Detail::default_height,
                std::string name = "");

        ~Window();

        void Close();  // calls dtor.

    };

}
