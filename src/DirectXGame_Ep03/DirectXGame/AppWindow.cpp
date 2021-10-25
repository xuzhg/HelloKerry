#include "AppWindow.h"

struct vec3
{
    float x, y, z;
};

struct vertex
{
    vec3 position;
};

AppWindow::AppWindow() :
    m_swap_chain(nullptr),
    m_vertex_buffer(nullptr)
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
    Window::onCreate();

    GraphicsEngine::get()->init();
    m_swap_chain = GraphicsEngine::get()->createSwapChain();

    RECT rc = this->getClientWindowRect();
    m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

    vertex list[] = {
        // x - y - z
        {-0.5f, -0.5f, 0.0f }, // Position 1
        { 0.0f,  0.5f, 0.0f }, // Position 2
        { 0.5f, -0.5f, 0.0f }, // Position 3
    };

    m_vertex_buffer = GraphicsEngine::get()->createVertexBuffer();

    UINT size_list = ARRAYSIZE(list);

    GraphicsEngine::get()->createShaders();
    UINT size_shader = 0;
    void* shader_byte_code = nullptr;
    GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);
    m_vertex_buffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void AppWindow::onUpdate()
{
    Window::onUpdate();

    GraphicsEngine::get()->getImmediateDeviceContext()
        ->clearRenderTargetColor(this->m_swap_chain, 0, 0, 1, 1);

    RECT rc = this->getClientWindowRect();
    GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
    GraphicsEngine::get()->setShaders();

    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);

    GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vertex_buffer->getSizeVertexList(), 0);

    m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
    Window::onDestroy();
    m_vertex_buffer->release();
    m_swap_chain->release();
    GraphicsEngine::get()->release();
}
