#pragma once

#include "WilloEngine/Rendering/Renderer.hpp"

namespace WilloEngine
{
    struct ImplRenderer
    {
        virtual bool Init(const RendererCreateInfo& createInfo) = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual void Render() = 0;
    };
}
