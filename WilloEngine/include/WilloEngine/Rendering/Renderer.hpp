#pragma once

#include "WilloEngine/Window.hpp"

namespace WilloEngine
{
    enum class RENDERER_IMPL
    {
        IMPL_D3D11,
        IMPL_VULKAN
    };

    struct RendererCreateInfo
    {
        WindowHandle windowHandle = nullptr;
        bool useDebugLayer = false;

        uint32_t renderResolutionWidth = 1;
        uint32_t renderResolutionHeight = 1;

        uint32_t numFramesInFlight = 3;
        bool vsync = false;
    };

    class Renderer : private PimplClass<struct ImplRenderer>
    {
    public:
        static bool Create(Renderer& renderer, const RendererCreateInfo& createInfo, RENDERER_IMPL rendererImpl);

        void Resize(uint32_t width, uint32_t height);

        void Render();
    };
}
