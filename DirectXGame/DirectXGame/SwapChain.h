#pragma once
#include <d3d11.h>
#include "Prerequisites.h"
class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system);
	bool present(bool vsync);
	~SwapChain();

private:
	IDXGISwapChain* m_swap_chain = NULL;
	ID3D11RenderTargetView* m_rtv = NULL;
	ID3D11DepthStencilView* m_dsv = NULL;
	RenderSystem* m_system = nullptr;

private: //DeviceContext
	friend class DeviceContext;
};

