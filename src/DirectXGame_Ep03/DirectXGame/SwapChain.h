#pragma once

#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	// initialize swapchian for a window
	bool init(HWND hwnd, UINT width, UINT height);

	// release
	bool release();

private:
	IDXGISwapChain* m_swap_chain;
};

