#pragma once

#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	// initialize swapchian for a window
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	// release
	bool release();

private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;

	friend class DeviceContext;
};

