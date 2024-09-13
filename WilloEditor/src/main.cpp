#include <iostream>

#include <tracy/Tracy.hpp>

#include <WilloEngine/Window.hpp>
#include <WilloEngine/Rendering/Renderer.hpp>
#include <WilloEngine/Inputmanager.hpp>

int main()
{
    WilloEngine::Window window;
    if (!WilloEngine::Window::Create(window, 800, 600, "Testing Window")) {
        std::cout << "Failed to create window\n";
        return 1;
    }

    WilloEngine::RendererCreateInfo rendererInfo = {
        .windowHandle = window.GetWindowHWND(),
        .useDebugLayer = true,

        .renderResolutionWidth = 800,
        .renderResolutionHeight = 600,

        .numFramesInFlight = 3,
        .vsync = true
    };

    WilloEngine::Renderer renderer;
    if (!WilloEngine::Renderer::Create(renderer, rendererInfo, WilloEngine::RENDERER_IMPL::IMPL_D3D11)) {
        std::cout << "Failed to create renderer\n";
        return 1;
    }

    WilloEngine::InputManager inputManager;
    if (!WilloEngine::InputManager::Create(inputManager, true)) {
        std::cout << "Failed to create input manager\n";
        return 1;
    }

    window.RegisterKeypressCallback([&](WilloEngine::KEY_CODE code, WilloEngine::INPUT_EVENT_TYPE eventType){
        ZoneScopedN("Keypress Event Trigger");
        inputManager.ReceiveKeypressEvent(code, eventType);
    });

    inputManager.SubscribeKey(WilloEngine::INPUT_EVENT_TYPE::KEY_RELEASED, [&](WilloEngine::KEY_CODE keyCode) {
        ZoneScopedN("Key Release Event");
        if (keyCode == WilloEngine::KEY_CODE::KEY_SPACE) {
            std::cout << "Pressed space\n";
            return;
        }
        std::cout << (char)keyCode << "\n";
    });

    std::cout << "Initialised\n";

    bool running = true;
    while (running)
    {
        FrameMark;

        {
            ZoneScopedN("Frame Update");
            running = window.PollEvents();
            inputManager.Update();

            renderer.Render();
        }
    }

    return 0;
}
