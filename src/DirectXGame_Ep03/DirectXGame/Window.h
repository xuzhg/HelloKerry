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

    RECT getClientWindowRect();
    void setHWND(HWND hwnd);

    // Events
    virtual void onCreate();
    virtual void onUpdate();
    virtual void onDestroy();

protected:
    HWND m_hwnd;
    bool m_is_run;
};