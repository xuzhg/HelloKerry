#include "Window.h"

Window* window = nullptr;

Window::Window()
{
    m_hwnd = NULL;
    m_is_run = false;
}

Window::~Window()
{

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,  WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        // Event fired when the window will be created
        window->onCreate();
        break;
    }

    case WM_DESTROY:
    {
        // Event fired when the window will be destroyed
        window->onDestory();
        ::PostQuitMessage(0);
        break;
    }

    default:
        return ::DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return NULL;
}


bool Window::init()
{
    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = WndProc;

    if (!::RegisterClassEx(&wc))
    {
        return false;
    }

    if (!window)
    {
        window = this;
    }

    // Creation of the window
    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass",
        L"DirectX Application",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1024,
        768,
        NULL,
        NULL,
        NULL,
        NULL);

    // if the creation fail return false
    if (!m_hwnd)
    {
        return false;
    }

    // show up the window
    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    m_is_run = true;
    return true;
}

bool Window::broadcast()
{
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    window->onUpdate();
    Sleep(0);
    return true;
}

bool Window::release()
{
    // Destroy the window
    if (!::DestroyWindow(m_hwnd))
    {
        return false;
    }

    return true;
}

bool Window::isRun()
{
    return m_is_run;
}

void Window::onDestory()
{
    m_is_run = false;
}
