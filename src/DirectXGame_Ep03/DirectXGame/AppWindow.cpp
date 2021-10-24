#include "AppWindow.h"

AppWindow::AppWindow()
{
    m_swap_chain = nullptr;
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
}

void AppWindow::onUpdate()
{
    Window::onUpdate();
}

void AppWindow::onDestory()
{
    Window::onDestory();

    m_swap_chain->release();
    GraphicsEngine::get()->release();
}
