#include <iostream>

#include <WilloEngine/Window.hpp>
#include <WilloEngine/Rendering/Renderer.hpp>
#include <WilloEngine/Inputmanager.hpp>

#include <WilloEngine/Profiling.hpp>

int main()
{
    WilloEngine::Window window;
    WilloEngine::Renderer renderer;
    WilloEngine::InputManager inputManager;

    {
        WILLO_ENGINE_PROFILE_N("Initialisation");
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

        if (!WilloEngine::Renderer::Create(renderer, rendererInfo, WilloEngine::RENDERER_IMPL::IMPL_D3D11)) {
            std::cout << "Failed to create renderer\n";
            return 1;
        }

        if (!WilloEngine::InputManager::Create(inputManager, true)) {
            std::cout << "Failed to create input manager\n";
            return 1;
        }

        window.RegisterKeypressCallback([&](WilloEngine::KEY_CODE code, WilloEngine::INPUT_EVENT_TYPE eventType){
            inputManager.ReceiveKeypressEvent(code, eventType);
        });

        inputManager.SubscribeKey(WilloEngine::INPUT_EVENT_TYPE::KEY_RELEASED, [&](WilloEngine::KEY_CODE keyCode) {
            WILLO_ENGINE_PROFILE_N_C("Key Release Event", WilloEngine::Profiling::Colour::Green);
            if (keyCode == WilloEngine::KEY_CODE::KEY_SPACE) {
                std::cout << "Pressed space\n";
                return;
            }
            std::cout << (char)keyCode << "\n";
        });

        std::cout << "Initialised\n";
    }

    bool running = true;
    while (running)
    {
        WILLO_ENGINE_PROFILE_FRAME_MARK();

        WILLO_ENGINE_PROFILE_N("Frame Update");
        running = window.PollEvents();
        inputManager.Update();
        
        renderer.Render();
    }

    return 0;
}
