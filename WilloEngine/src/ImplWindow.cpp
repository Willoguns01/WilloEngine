#include "ImplWindow.hpp"

#include <SDL2/SDL_syswm.h>

#include <iostream>

#include <WilloEngine/Profiling.hpp>

namespace WilloEngine
{
    bool Window::Create(Window& window, uint32_t width, uint32_t height, const std::string& title)
    {
        window.impl = std::make_shared<ImplWindow>();
        if (!window.impl->Init(width, height, title)) {
            window.impl.reset();
            return false;
        }
        return true;
    }

    bool ImplWindow::Init(uint32_t width, uint32_t height, const std::string& title)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Gray);

        if (!InitSDLWindow(width, height, title)) {
            std::cout << "Failed initialising SDL windowing\n";
            return false;
        }

        return true;
    }

    bool ImplWindow::InitSDLWindow(uint32_t width, uint32_t height, const std::string& title)
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Gray);

        SDL_Init(SDL_INIT_VIDEO);

        SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE;
        _sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
        if (_sdlWindow == nullptr) {
            std::cout << "Failed to create SDL window: " << SDL_GetError() << "\n";
            return false;
        }

        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(_sdlWindow, &wmInfo);
        _hwnd = wmInfo.info.win.window;

        return true;
    }

    WindowHandle Window::GetWindowHWND() const { return impl->GetWindowHWND(); }
    WindowHandle ImplWindow::GetWindowHWND() const
    {
        return (WindowHandle)_hwnd;
    }

    void Window::RegisterKeypressCallback(std::function<void(KEY_CODE,INPUT_EVENT_TYPE)> func) { impl->RegisterKeypressCallback(func); }
    void ImplWindow::RegisterKeypressCallback(std::function<void(KEY_CODE,INPUT_EVENT_TYPE)> func)
    {
        _keypressCallback = func;
    }

    bool Window::PollEvents() { return impl->PollEvents(); }
    bool ImplWindow::PollEvents()
    {
        WILLO_ENGINE_PROFILE_C(WilloEngine::Profiling::Colour::Gray);

        bool returnValue = true;
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                returnValue = false;
            }

            // callbacks to the input manager
            if (_keypressCallback != nullptr) {
                if (event.type == SDL_KEYDOWN) {
                    _keypressCallback((KEY_CODE)event.key.keysym.sym, INPUT_EVENT_TYPE::KEY_PRESSED);
                }
                if (event.type == SDL_KEYUP) {
                    _keypressCallback((KEY_CODE)event.key.keysym.sym, INPUT_EVENT_TYPE::KEY_RELEASED);
                }
            }
        }

        // if true, application should keep running
        // if false, window close
        return returnValue;
    }
}
