#pragma once

#include "ImplRenderer.hpp"

#include <d3d11_4.h>
#include <dxgi1_2.h>
#include <wrl.h>

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

namespace WilloEngine
{
    struct D3D11ImplRenderer : public ImplRenderer
    {
        bool CreateSwapchainResources(uint32_t width, uint32_t height);
        void DestroySwapchainResources();

        ComPtr<ID3D11Device3> _device = nullptr;
        ComPtr<ID3D11DeviceContext3> _deviceContext = nullptr;

        ComPtr<IDXGIFactory2> _dxgiFactory = nullptr;
        ComPtr<IDXGISwapChain1> _swapchain = nullptr;

        uint32_t _renderWidth = 1;
        uint32_t _renderHeight = 1;

        bool _useVsync = false;

        // TODO: some mechanism to render to other targets (i.e. editor scene view)
        ComPtr<ID3D11RenderTargetView> _renderTarget = nullptr;

        bool Init(const RendererCreateInfo& createInfo) override;

        void Resize(uint32_t width, uint32_t height) override;

        void Render() override;
    };
}
