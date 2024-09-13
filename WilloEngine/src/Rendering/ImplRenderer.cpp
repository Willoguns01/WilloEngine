#include "ImplRenderer.hpp"

#include "D3D11ImplRenderer.hpp"

// TODO: replace cout calls with proper logging
#include <iostream>

namespace WilloEngine
{
    bool Renderer::Create(Renderer& renderer, const RendererCreateInfo& createInfo, RENDERER_IMPL rendererImpl)
    {
        switch (rendererImpl)
        {
            case RENDERER_IMPL::IMPL_D3D11: {
                renderer.impl = std::make_shared<D3D11ImplRenderer>();
            }
                break;
            case RENDERER_IMPL::IMPL_VULKAN: {
                std::cout << "Vulkan backend not implemented.\nJust going to use D3D11 renderer backend for now.\n";
                renderer.impl = std::make_shared<D3D11ImplRenderer>();
            }
                break;
        }

        if (!renderer.impl->Init(createInfo)) {
            renderer.impl.reset();
            return false;
        }
        return true;
    }

    void Renderer::Resize(uint32_t width, uint32_t height) {
        impl->Resize(width, height);
    }

    void Renderer::Render() {
        impl->Render();
    }
}
