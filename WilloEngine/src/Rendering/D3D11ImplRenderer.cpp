#include "D3D11ImplRenderer.hpp"

#include <iostream>

#include <tracy/Tracy.hpp>

namespace WilloEngine
{
    bool D3D11ImplRenderer::CreateSwapchainResources(uint32_t width, uint32_t height)
    {
        ZoneScoped;

        ComPtr<ID3D11Texture2D> backBuffer = nullptr;
        if (FAILED(_swapchain->GetBuffer(
            0,
            IID_PPV_ARGS(&backBuffer)
        ))) {
            std::cout << "Failed to get swapchain backbuffer\n";
            return false;
        }

        if (FAILED(_device->CreateRenderTargetView(
            backBuffer.Get(),
            nullptr,
            &_renderTarget
        ))) {
            std::cout << "Failed to create swapchain backbuffer RTV\n";
            return false;
        }

        return true;
    }

    void D3D11ImplRenderer::DestroySwapchainResources()
    {
        _renderTarget.Reset();
    }

    bool D3D11ImplRenderer::Init(const RendererCreateInfo& createInfo)
    {
        ZoneScoped;

        if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory)))) {
            std::cout << "Failed to create DXGI factory\n";
            return false;
        }

        ComPtr<ID3D11Device> device = nullptr;
        ComPtr<ID3D11DeviceContext> deviceContext = nullptr;

        constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_1;

        UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        if (createInfo.useDebugLayer)
            deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

        if (FAILED(D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            &deviceFeatureLevel,
            1,
            D3D11_SDK_VERSION,
            &device,
            nullptr,
            &deviceContext
        ))) {
            std::cout << "Failed to create D3D11 device\n";
            return false;
        }

        if (FAILED(device.As(&_device))) {
            std::cout << "Failed to get D3D11 Device3\n";
            return false;
        }

        if (FAILED(deviceContext.As(&_deviceContext))) {
            std::cout << "Failed to get D3D11 DeviceContext3\n";
            return false;
        }

        DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {
            .Width = createInfo.renderResolutionWidth,
            .Height = createInfo.renderResolutionHeight,
            .Format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM,
            .SampleDesc = {
                .Count = 1,
                .Quality = 0
            },
            .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
            .BufferCount = createInfo.numFramesInFlight,
            .Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH,
            .SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD,
            .Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
        };

        if (_useVsync)
            swapchainDesc.Flags = 0;

        DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapchainFullscreenDesc = {
            .Windowed = true
        };

        if (FAILED(_dxgiFactory->CreateSwapChainForHwnd(
            _device.Get(),
            createInfo.windowHandle,
            &swapchainDesc,
            &swapchainFullscreenDesc,
            nullptr,
            &_swapchain
        ))) {
            std::cout << "Failed to create DXGI swapchain\n";
            return false;
        }

        if (!CreateSwapchainResources(createInfo.renderResolutionWidth, createInfo.renderResolutionHeight)) {
            std::cout << "Failed to create swapchain resources\n";
            return false;
        }

        _renderWidth = createInfo.renderResolutionWidth;
        _renderHeight = createInfo.renderResolutionHeight;
        _useVsync = createInfo.vsync;

        return true;
    }

    void D3D11ImplRenderer::Resize(uint32_t width, uint32_t height)
    {
        ZoneScoped;

        _deviceContext->Flush();

        DestroySwapchainResources();

        if (FAILED(_swapchain->ResizeBuffers(
            0,
            width,
            height,
            DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM,
            0
        ))) {
            std::cout << "Failed to resize swapchain buffers\n";
            return;
        }

        CreateSwapchainResources(width, height);

        _renderWidth = width;
        _renderHeight = height;
    }

    void D3D11ImplRenderer::Render()
    {
        ZoneScoped;

        D3D11_VIEWPORT viewport = {
            .TopLeftX = 0,
            .TopLeftY = 0,
            .Width = static_cast<float>(_renderWidth),
            .Height = static_cast<float>(_renderHeight),
            .MinDepth = 0.0f,
            .MaxDepth = 1.0f
        };

        constexpr float clearColour[] = {0.1f, 0.1f, 0.1f, 1.0f};

        _deviceContext->ClearRenderTargetView(_renderTarget.Get(), clearColour);
        _deviceContext->RSSetViewports(1, &viewport);
        _deviceContext->OMSetRenderTargets(1, _renderTarget.GetAddressOf(), nullptr);

        UINT presentFlags = 0;
        if (!_useVsync)
            presentFlags = DXGI_PRESENT_ALLOW_TEARING;
        _swapchain->Present(_useVsync, presentFlags);
    }
}
