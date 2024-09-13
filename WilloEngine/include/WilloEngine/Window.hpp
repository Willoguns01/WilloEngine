#pragma once

#include "WilloEngine/PimplClass.hpp"

// TODO: toggle between windows and whatever depending on build opts
#include <windows.h>

#include <string>
#include <functional>

#include "WilloEngine/InputManager.hpp"

namespace WilloEngine
{
    // see above
    typedef HWND WindowHandle;

    class Window : private PimplClass<struct ImplWindow>
    {
    public:
        static bool Create(Window& window, uint32_t width, uint32_t height, const std::string& title);

        WindowHandle GetWindowHWND() const;

        void RegisterKeypressCallback(std::function<void(KEY_CODE,INPUT_EVENT_TYPE)> func);

        bool PollEvents();
    };
}
