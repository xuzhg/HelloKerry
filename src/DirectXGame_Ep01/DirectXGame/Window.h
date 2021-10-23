#pragma once

#include <windows.h>

class Window
{
public:
    Window();
    ~Window();

    // Initialize the window
    bool init();

    bool broadcast();

    // Release the window
    bool release();

    bool isRun();

    // Events
    virtual void onCreate() =0;
    virtual void onUpdate() =0;
    virtual void onDestory();

protected:
    HWND m_hwnd;
    bool m_is_run;
};