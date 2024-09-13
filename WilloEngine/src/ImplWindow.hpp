#pragma once

#include "WilloEngine/Window.hpp"

#include <SDL2/SDL.h>

namespace WilloEngine
{
    struct ImplWindow
    {
        SDL_Window* _sdlWindow = nullptr;
        void* _hwnd = nullptr;

        std::function<void(KEY_CODE,INPUT_EVENT_TYPE)> _keypressCallback = nullptr;

        bool Init(uint32_t width, uint32_t height, const std::string& title);

        bool InitSDLWindow(uint32_t width, uint32_t height, const std::string& title);

        WindowHandle GetWindowHWND() const;

        void RegisterKeypressCallback(std::function<void(KEY_CODE,INPUT_EVENT_TYPE)> func);

        bool PollEvents();
    };
}
