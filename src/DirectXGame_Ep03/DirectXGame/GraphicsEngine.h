#pragma once

// DirectX 12
#include <d3d11.h>

class SwapChain;

class GraphicsEngine
{
public:
    GraphicsEngine();
    ~GraphicsEngine();

    // initialize the graphicsEngine and DirectX 11 Device
    bool init();

    // Release all the resources loaded
    bool release();

public:
    SwapChain* createSwapChain();

public:
    static GraphicsEngine* get();
private:
    ID3D11Device* m_d3d_device;
    D3D_FEATURE_LEVEL m_feature_level;
    ID3D11DeviceContext* m_imm_context;

    IDXGIDevice* m_dxgi_device;
    IDXGIAdapter* m_dxgi_adapter;
    IDXGIFactory* m_dxgi_factory;

private:
    friend class SwapChain;
};

