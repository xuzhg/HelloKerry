#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"

GraphicsEngine::GraphicsEngine()
{
    m_d3d_device = nullptr;
    m_feature_level = D3D_FEATURE_LEVEL_11_0;

    m_dxgi_device = nullptr;
    m_dxgi_adapter = nullptr;
    m_dxgi_factory = nullptr;
    m_imm_device_context = nullptr;
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };

    UINT num_driver_type = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_0
    };
    UINT num_feature_levels = ARRAYSIZE(feature_levels);

    ID3D11DeviceContext* imm_context;

    HRESULT res = 0;
    for (UINT driver_type_index = 0; driver_type_index < num_driver_type; driver_type_index++)
    {
        res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
            num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &imm_context);

        if (SUCCEEDED(res))
        {
            break;
        }
    }

    if (FAILED(res))
    {
        return false;
    }

    m_imm_device_context = new DeviceContext(imm_context);

    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
    m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

    return true;
}

bool GraphicsEngine::release()
{
    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();

    m_imm_device_context->release();
    m_d3d_device->Release();
    return true;
}

SwapChain* GraphicsEngine::createSwapChain()
{
    return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
    return m_imm_device_context;
}

GraphicsEngine* GraphicsEngine::get()
{
    static GraphicsEngine engine;
    return &engine;
}
